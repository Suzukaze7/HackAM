from io import TextIOWrapper
import shutil
import subprocess
from concurrent.futures import Future, ThreadPoolExecutor, wait
from multiprocessing import cpu_count
from pathlib import Path
from time import sleep
from typing import Callable, Iterable
from requests import get, post
from bs4 import BeautifulSoup
from func_timeout import FunctionTimedOut, func_set_timeout


class Run:
    def __init__(self, src: str | Path):
        self.__src: Path = Path(src)
        if self.__src.suffix == '.cpp':
            self.__dst = self.__src.with_suffix('.exe')
            if not self.__dst.exists():
                subprocess.run(
                    ['g++', '-std=c++17', self.__src, '-o', self.__dst])
            self.__is_cpp = True
        else:
            self.__dst = self.__src
            self.__is_cpp = False

    def __str__(self):
        return str(self.__src)

    def run(self, stdin=None, stdout=None, timeout=None) -> subprocess.CompletedProcess:
        if self.__is_cpp:
            return subprocess.run(self.__dst, stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')
        else:
            return subprocess.run(['python', self.__dst], stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')


class HackAM:
    def __init__(self, base_dir: str | Path = 'code', thread_count: int = cpu_count() - 3):
        self.__BASE_DIR: Path = Path(base_dir)
        self.__THREAD_COUNT: int = thread_count
        self.__HACKED_LOG: Path = self.__BASE_DIR / 'hacked.log'

    def __del__(self):
        self.rm_exe()

    def __red(self, s):
        print('\033[91m', s, '\033[0m', sep='')

    def __green(self, s):
        print('\033[32m', s, '\033[0m', sep='')

    def __yellow(self, s):
        print('\033[33m', s, '\033[0m', sep='')

    @func_set_timeout(30)
    def __start_hack(self, input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path):
        in_file: Path = hacked_dir / '1.in'
        out_file: Path = hacked_dir / '1.out'
        res_file: Path = hacked_dir / '1.result'
        while True:
            input_file.run(stdout=in_file.open(
                'w', encoding='utf-8')).check_returncode()

            std_file.run(in_file.open('r', encoding='utf-8'),
                         out_file.open('w', encoding='utf-8')).check_returncode()

            hacked_file.run(in_file.open('r', encoding='utf-8'),
                            res_file.open('w', encoding='utf-8')).check_returncode()

            with out_file.open('r', encoding='utf-8') as f:
                out = [line.strip() for line in f.readlines()]
            with res_file.open('r', encoding='utf-8') as f:
                result = [line.strip() for line in f.readlines()]

            if out != result:
                break

    def __run_hack(self, input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path, log: TextIOWrapper):
        hacked_flag = hacked_dir / 'hacked'
        if hacked_flag.exists():
            return

        self.__green(f'Hacking: {input_file} {std_file} {hacked_file}')
        try:
            self.__start_hack(input_file, std_file, hacked_file, hacked_dir)
        except FunctionTimedOut:
            self.__green(f'Accepted: {hacked_file}')
            for data in hacked_dir.glob('1.*'):
                data.unlink()
        except Exception as e:
            s = f'Error occurred: {hacked_file} {e}'
            self.__red(s)
            print(log.write(s + '\n'))
        else:
            s = f'Hack successfully: {hacked_file}'
            self.__red(s)
            print(log.write(s + '\n'))

        hacked_flag.touch()

    def __get_typed_path(self, dir: Path, name: str | Path) -> Path:
        path = (dir / name).with_suffix('.cpp')
        if not path.exists():
            path = path.with_suffix('.py')
            if not path.exists():
                return None
        return path

    def process_submission(self, table: Iterable, get_code: Callable[[str], None]):
        self.__BASE_DIR.mkdir(exist_ok=True)
        with ThreadPoolExecutor(self.__THREAD_COUNT) as executor, self.__HACKED_LOG.open('w+', encoding='utf-8') as log:
            res: list[Future] = []
            for problem_id, lang, submission_id in table():
                problem_dir: Path = self.__BASE_DIR / problem_id
                lang_dir: Path = problem_dir / lang
                hacked_dir: Path = lang_dir / submission_id
                hacked_file: Path = hacked_dir / f'hacked.{lang}'

                # 尝试定义 input.cpp 文件路径
                input_file = self.__get_typed_path(problem_dir, 'input')
                if not input_file:
                    self.__yellow(
                        f'No input files for {problem_dir.name}, skipping...')
                    continue

                # 尝试定义 std.cpp 文件路径
                std_file = self.__get_typed_path(problem_dir, 'std')
                if not std_file:
                    self.__yellow(
                        f'No std files for {problem_dir.name}, skipping...')
                    continue

                hacked_dir.mkdir(exist_ok=True, parents=True)
                with hacked_file.open('w', encoding='utf-8') as f:
                    f.write(get_code(submission_id))

                input_file: Run = Run(input_file)
                std_file: Run = Run(std_file)
                hacked_file: Run = Run(hacked_file)

                res.append(executor.submit(self.__run_hack,
                           input_file, std_file, hacked_file, hacked_dir, log))

                sleep(10)

            wait(res)

    def NowCoder(self, contest_id: int | str, t: str):
        """
        t: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        """

        def table():
            table_url = f'https://ac.nowcoder.com/acm-heavy/acm/contest/status-list?statusTypeFilter=5&id={contest_id}&page='
            json = get(table_url).json()
            page_cnt = json['data']['basicInfo']['pageCount']

            for i in range(page_cnt):
                cur_url = table_url + str(i + 1)
                json = get(cur_url).json()
                for sub in json['data']['data']:
                    lang = sub['languageCategoryName']
                    if lang == 'C++':
                        lang = 'cpp'
                    elif lang == 'Python3' or lang == 'PyPy3':
                        lang = 'py'
                    else:
                        continue
                    yield sub['index'], lang, str(sub['submissionId'])

        def get_code(submission_id: str):
            submission_url = 'https://ac.nowcoder.com/acm/contest/view-submission?submissionId=' + submission_id
            res = get(submission_url, cookies={'t': t})
            soup = BeautifulSoup(res.text, 'html.parser')
            return soup.find('pre').text

        self.process_submission(table, get_code)

    def Codeforces(self, contest_id: int | str, csrf_token: str, jsession_id: str):
        """
        csrf_token: 按 F12 打开开发者工具，选择网络->打开一个提交->找到 submitSource 包 -> 负载
        jsession_id: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        """

        def table():
            table_url = f'https://codeforces.com/api/contest.status?contestId={contest_id}'
            json = get(table_url).json()
            for submission in json['result']:
                if submission['verdict'] != 'OK':
                    continue

                lang: str = submission['programmingLanguage']
                if lang.startswith('C++'):
                    lang = 'cpp'
                elif lang.startswith(('Python', 'PyPy')):
                    lang = 'py'
                else:
                    continue

                yield submission['problem']['index'], lang, str(submission['id'])

        def get_code(submission_id: str):
            submission_url = f'https://codeforces.com/data/submitSource?submissionId={submission_id}'
            header = {
                'Referer': f'https://codeforces.com/contest/{contest_id}/status',
                'X-Csrf-Token': csrf_token,
                'cookie': f'JSESSIONID={jsession_id}',
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0',
            }
            self.__red(f'pull: {contest_id}')
            res = post(submission_url, headers=header).json()
            return res['source']

        self.process_submission(table, get_code)

    def clear_hacked_files(self):
        self.__HACKED_LOG.unlink(True)
        for x_path in self.__BASE_DIR.iterdir():
            for dirs in x_path.iterdir():
                if dirs.is_dir():
                    shutil.rmtree(dirs)

    def rm_exe(self):
        for exe in self.__BASE_DIR.rglob('*.exe'):
            exe.unlink()


if __name__ == '__main__':
    am = HackAM()
    am.NowCoder(82707, 'A4965E404E764FB0596C7BE8B815FAEF')
