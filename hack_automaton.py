from abc import ABC, abstractmethod
from functools import reduce
from io import TextIOWrapper
from operator import add
import shutil
import subprocess
from concurrent.futures import Future, ThreadPoolExecutor, wait
from multiprocessing import cpu_count
from pathlib import Path
from time import sleep
from typing import Callable, Self
import colorama
from bs4 import BeautifulSoup
from func_timeout import FunctionTimedOut, func_set_timeout
import requests
import sqlite3

colorama.init(True)


def red(s):
    print(colorama.Fore.RED + s)


def green(s):
    print(colorama.Fore.GREEN + s)


def yellow(s):
    print(colorama.Fore.YELLOW + s)


class Run:
    def __init__(self, src: str | Path, lang: str = None):
        self.__SRC: Path = Path(src)

        if not lang:
            DFT = {
                '.cpp': 'cpp17',
                '.py': 'py'
            }
            lang = DFT[self.__SRC.suffix]

        self.__LANG: str = lang
        if lang.startswith('cpp'):
            self.__DST = self.__SRC.with_suffix('.exe')
            subprocess.run(['g++', '-DONLINE_JUDGE', f'-std=c++{lang[3:]}',
                            self.__SRC, '-o', self.__DST], stderr=subprocess.DEVNULL)

    def __str__(self):
        return str(self.__SRC)

    def run(self, stdin=None, stdout=None, timeout=None) -> subprocess.CompletedProcess:
        if self.__LANG.startswith('cpp'):
            return subprocess.run(self.__DST, stdin=stdin, stdout=stdout, stderr=subprocess.DEVNULL, timeout=timeout, check=True, encoding='utf-8')
        else:
            return subprocess.run(['python', self.__SRC], stdin=stdin, stdout=stdout, stderr=subprocess.DEVNULL, timeout=timeout, check=True, encoding='utf-8')


class TargetOJ(ABC):
    @abstractmethod
    def get_submissions(self) -> dict[str, list[tuple[int, str, int]]]:
        pass

    @abstractmethod
    def get_code(self, sub_id: int) -> str:
        pass

    def _cyclin_request(self, err_msg: str, request: Callable[..., requests.Response], *args, **kwargs) -> requests.Response:
        while True:
            res = request(*args, **kwargs)
            if res.ok:
                return res
            yellow(f'{err_msg} {res.reason}, wait for 30s')
            sleep(30)


class NowCoder(TargetOJ):
    def __init__(self, contest_id: int, t: str):
        '''
        t: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        '''
        self.__CONTEST_ID = contest_id
        self.__T = t

    def get_submissions(self) -> dict[str, list[tuple[int, str, int]]]:
        table_url = f'https://ac.nowcoder.com/acm-heavy/acm/contest/status-list?statusTypeFilter=5&id={self.__CONTEST_ID}&page='
        json = self._cyclin_request(
            'get nowcoder all submission id', requests.get, table_url).json()
        page_cnt = json['data']['basicInfo']['pageCount']

        subs = {}
        for i in range(page_cnt):
            cur_url = table_url + str(i + 1)
            json = requests.get(cur_url).json()
            for submission in json['data']['data']:
                lang: str = submission['languageCategoryName']
                sub: tuple = (submission['submissionId'],)
                if lang == 'C++':
                    sub += ('cpp', 17)
                elif lang == 'Python3' or lang == 'PyPy3':
                    sub = ('py',)
                else:
                    continue
                subs.setdefault(submission['index'], []).append(sub)
        return subs

    def get_code(self, submission_id: int) -> str:
        submission_url = f'https://ac.nowcoder.com/acm/contest/view-submission?submissionId={submission_id}'
        res = self._cyclin_request(
            f'get nowcoder {submission_id} submission code', requests.get, submission_url, cookies={'t': self.__T})
        soup = BeautifulSoup(res.text, 'html.parser')
        return soup.find('pre').get_text()


class Codeforces(TargetOJ):
    def __init__(self, contest_id: int, csrf_token: str, jsession_id: str):
        '''
        csrf_token: 按 F12 打开开发者工具，选择网络->打开一个提交->找到 submitSource 包 -> 负载

        jsession_id: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        '''
        super().__init__()
        self.__CONTEST_ID = contest_id
        self.__CSRF_TOKEN = csrf_token
        self.__JSESSION_ID = jsession_id

    def get_submissions(self) -> dict[str, list[tuple[int, str, int]]]:
        table_url = f'https://codeforces.com/api/contest.status?contestId={self.__CONTEST_ID}'
        json = self._cyclin_request(
            'get codeforces all submission id', requests.get, table_url).json()

        subs = {}
        for submission in json['result']:
            if 'verdict' not in submission or submission['verdict'] != 'OK':
                continue

            lang: str = submission['programmingLanguage']
            sub: tuple = (submission['id'],)
            if lang.startswith('C++'):
                sub += ('cpp', int(lang[3:5]))
            elif lang.startswith(('Python', 'PyPy')):
                sub += ('py',)
            else:
                continue

            subs.setdefault(submission['problem']['index'], []).append(sub)
        return subs

    def get_code(self, submission_id: int) -> str:
        submission_url = f'https://codeforces.com/data/submitSource?submissionId={submission_id}'
        header = {
            'Referer': f'https://codeforces.com/contest/{self.__CONTEST_ID}/status',
            'X-Csrf-Token': self.__CSRF_TOKEN,
            'cookie': f'JSESSIONID={self.__JSESSION_ID}',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0',
        }
        res = self._cyclin_request(
            f'get codeforces {submission_id} submission code', requests.post, submission_url, headers=header).json()
        return res['source'].replace('\r', '')


class SqliteWrapper:
    class Field:
        def __init__(self, field: tuple | None):
            if not field:
                self.exists = False
                self.lang = None
                self.hacked = False
            else:
                self.exists = True
                self.lang = field[1]
                self.hacked = field[2]

    def __init__(self, db: Path):
        self.__DB: Path = db

    def __enter__(self) -> Self:
        self.__conn = sqlite3.connect(
            self.__DB, isolation_level=None, check_same_thread=False)
        self.__cur = self.__conn.cursor()
        self.__cur.execute('''CREATE TABLE IF NOT EXISTS hack (
                            sub_id INTEGER PRIMARY KEY,
                            lang TEXT,
                            hacked INTEGER
                        ) WITHOUT ROWID''')
        return self

    def __exit__(self, type, value, tb):
        self.__cur.close()
        self.__conn.close()

    def get(self, sub_id: int) -> Field:
        self.__cur.execute('SELECT * FROM hack where sub_id = ?', (sub_id,))
        return self.Field(self.__cur.fetchone())

    def add(self, sub_id: int, lang: str):
        self.__cur.execute(
            'INSERT INTO hack VALUES (?, ?, FALSE)', (sub_id, lang))

    def update(self, sub_id: int = -1, hacked: bool = True):
        if sub_id == -1:
            self.__cur.execute('UPDATE hack SET hacked = ?', (hacked,))
        else:
            self.__cur.execute(
                'UPDATE hack SET hacked = ? where sub_id = ?', (hacked, sub_id))


class HackAM:
    def __init__(self, target_oj: TargetOJ, base_dir: str = 'hack', thread_count: int = cpu_count()):
        self.__TARGET_OJ = target_oj
        self.__BASE_DIR = Path(base_dir)
        self.__THREAD_COUNT = thread_count
        self.__LOG: Path = self.__BASE_DIR / 'hack.log'
        self.__DB: Path = self.__BASE_DIR / 'hack.db'

    def __del__(self):
        self.clear_exe()

    @func_set_timeout(30)
    def __start_hack(self, input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path):
        in_file: Path = hacked_dir / '1.in'
        out_file: Path = hacked_dir / '1.out'
        res_file: Path = hacked_dir / '1.result'
        while True:
            input_file.run(stdout=in_file.open('w', encoding='utf-8'))
            std_file.run(in_file.open('r', encoding='utf-8'),
                         out_file.open('w', encoding='utf-8'))
            hacked_file.run(in_file.open('r', encoding='utf-8'),
                            res_file.open('w', encoding='utf-8'))

            with out_file.open('r', encoding='utf-8') as f:
                out = reduce(add, map(lambda s: s.split(), f.readlines()))
            with res_file.open('r', encoding='utf-8') as f:
                result = reduce(add, map(lambda s: s.split(), f.readlines()))

            if out != result:
                break

    def __run_hack(self, input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path, log: TextIOWrapper):
        green(f'Hacking: {input_file} {std_file} {hacked_file}')
        try:
            self.__start_hack(input_file, std_file, hacked_file, hacked_dir)
        except FunctionTimedOut:
            green(f'Accepted: {hacked_file}')
            for data in hacked_dir.glob('1.*'):
                data.unlink()
        except Exception as e:
            s = f'Error occurred: {hacked_file} {e}'
            red(s)
            log.write(s + '\n')
            log.flush()
        else:
            s = f'Hack successfully: {hacked_file}'
            red(s)
            log.write(s + '\n')
            log.flush()

    def __get_typed_path(self, dir: Path, name: str) -> Path:
        path: Path = dir / (name + '.cpp')
        if not path.exists():
            path = path.with_suffix('.py')
            if not path.exists():
                return None
        return path

    def __hacked_flag_wrap(self, sql: SqliteWrapper, sub_id: int) -> Callable[[Future], None]:
        return lambda fut: sql.update(sub_id)

    def get_and_hack(self):
        self.__BASE_DIR.mkdir(exist_ok=True)
        with ThreadPoolExecutor(self.__THREAD_COUNT) as executor, SqliteWrapper(self.__DB) as sql, self.__LOG.open('w+', encoding='utf-8') as log:
            res: list[Future] = []
            for prob_id, subs in self.__TARGET_OJ.get_submissions().items():
                prob_dir: Path = self.__BASE_DIR / prob_id
                prob_dir.mkdir(exist_ok=True)

                input_file = self.__get_typed_path(prob_dir, 'input')
                if not input_file:
                    yellow(
                        f'No input files for {prob_dir.name}, skipping...')
                    continue

                std_file = self.__get_typed_path(prob_dir, 'std')
                if not std_file:
                    yellow(
                        f'No std files for {prob_dir.name}, skipping...')
                    continue

                input_file = Run(input_file)
                std_file = Run(std_file)

                sub_dir: Path = prob_dir / 'submissions'
                sub_dir.mkdir(exist_ok=True)
                for sub_id, *lang in subs:
                    hacked_dir: Path = sub_dir / str(sub_id)
                    hacked_file: Path = hacked_dir / f'hacked.{lang[0]}'
                    lang = ''.join(map(str, lang))

                    sql_res = sql.get(sub_id)
                    if sql_res.hacked:
                        continue

                    if not sql_res.exists:
                        hacked_dir.mkdir(exist_ok=True)
                        with hacked_file.open('w', encoding='utf-8') as f:
                            f.write(self.__TARGET_OJ.get_code(sub_id))
                        sql.add(sub_id, lang)

                    hacked_file = Run(hacked_file, lang)

                    fut = executor.submit(
                        self.__run_hack, input_file, std_file, hacked_file, hacked_dir, log)
                    fut.add_done_callback(self.__hacked_flag_wrap(sql, sub_id))
                    res.append(fut)

                    sleep(10)

            wait(res)

    def get_code(self, specified_ids : str = ''):
        '''
            Args:
                specified_ids (str): 指定题号爬取，若为空，爬取全部题目代码.
        '''
        self.__BASE_DIR.mkdir(exist_ok=True)
        with SqliteWrapper(self.__DB) as sql, self.__LOG.open('w+', encoding='utf-8') as log:
            self.__BASE_DIR.mkdir(exist_ok=True)
            for prob_id, subs in self.__TARGET_OJ.get_submissions().items():
                if specified_ids and specified_ids.find(prob_id) == -1:
                    continue
                    
                prob_dir: Path = self.__BASE_DIR / prob_id
                prob_dir.mkdir(exist_ok=True)
                sub_dir: Path = prob_dir / 'submissions'
                sub_dir.mkdir(exist_ok=True)
                for sub_id, *lang in subs:
                    hacked_dir: Path = sub_dir / str(sub_id)
                    hacked_file: Path = hacked_dir / f'hacked.{lang[0]}'
                    lang = ''.join(map(str, lang))

                    sql_res = sql.get(sub_id)
                    if not sql_res.exists:
                        hacked_dir.mkdir(exist_ok=True)
                        with hacked_file.open('w', encoding='utf-8') as f:
                            f.write(self.__TARGET_OJ.get_code(sub_id))
                        sql.add(sub_id, lang)

    def hack(self):
        self.__BASE_DIR.mkdir(exist_ok=True)
        with ThreadPoolExecutor(self.__THREAD_COUNT) as executor, SqliteWrapper(self.__DB) as sql, self.__LOG.open('w+', encoding='utf-8') as log:
            res: list[Future] = []
            for prob_dir in self.__BASE_DIR.iterdir():
                input_file = self.__get_typed_path(prob_dir, 'input')
                if not input_file:
                    yellow(
                        f'No input files for {prob_dir.name}, skipping...')
                    continue

                std_file = self.__get_typed_path(prob_dir, 'std')
                if not std_file:
                    yellow(
                        f'No std files for {prob_dir.name}, skipping...')
                    continue

                input_file = Run(input_file)
                std_file = Run(std_file)

                sub_dir: Path = prob_dir / 'submissions'
                sub_dir.mkdir(exist_ok=True)
                for hacked_dir in sub_dir.iterdir():
                    sub_id : str = hacked_dir.stem
                    sql_res = sql.get(sub_id)
                    if sql_res.hacked:
                        continue
                    lang = sql_res.lang
                    print(sub_id, lang)
                    if not lang:
                        continue

                    hacked_file: Path = hacked_dir / f'hacked.cpp'
                    if not hacked_file.exists():
                        hacked_file: Path = hacked_dir / f'hacked.py'

                    hacked_file = Run(hacked_file, lang)
                    fut = executor.submit(
                        self.__run_hack, input_file, std_file, hacked_file, hacked_dir, log)
                    fut.add_done_callback(self.__hacked_flag_wrap(sql, sub_id))
                    res.append(fut)

                    sleep(10)

            wait(res)

    def clear_hacked_files(self):
        self.__LOG.unlink(True)
        self.__DB.unlink(True)
        for prob_dir in self.__BASE_DIR.iterdir():
            shutil.rmtree(prob_dir / 'submissions', ignore_errors=True)

    def clear_hacked_flags(self):
        self.__LOG.unlink(True)
        with SqliteWrapper(self.__DB) as sql:
            sql.update()

    def clear_exe(self):
        for exe in self.__BASE_DIR.rglob('*.exe'):
            exe.unlink()


if __name__ == '__main__':
    contest = '1984'
    csrf = '18c0ab2f9de532dde4429a799f91ad11'
    jsession = 'E126E5AFD2752CFB9C0DE84DDF27B51E'
    target_oj = Codeforces(contest, csrf, jsession)
    am = HackAM(target_oj, 'cf'+contest)
    # am.get_and_hack()
    # am.get_code("BD")
    am.hack()
