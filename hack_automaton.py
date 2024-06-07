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
from typing import Callable
import colorama
from bs4 import BeautifulSoup
from func_timeout import FunctionTimedOut, func_set_timeout
import requests

colorama.init(True)


def red(s):
    print(colorama.Fore.RED + s)


def green(s):
    print(colorama.Fore.GREEN + s)


def yellow(s):
    print(colorama.Fore.YELLOW + s)


class Run:
    def __init__(self, src: str | Path):
        self.__src: Path = Path(src)
        if self.__src.suffix == '.cpp':
            self.__dst = self.__src.with_suffix('.exe')
            subprocess.run(['g++', '-D', 'ONLINE_JUDGE',
                           '-std=c++17', self.__src, '-o', self.__dst])
            self.__is_cpp = True
        else:
            self.__dst = self.__src
            self.__is_cpp = False

    def __str__(self):
        return str(self.__src)

    def run(self, stdin=None, stdout=None, timeout=None) -> subprocess.CompletedProcess:
        if self.__is_cpp:
            return subprocess.run(self.__dst, stdin=stdin, stdout=stdout, timeout=timeout, stderr=subprocess.DEVNULL, check=True, encoding='utf-8')
        else:
            return subprocess.run(['python', self.__dst], stdin=stdin, stdout=stdout, stderr=subprocess.DEVNULL, timeout=timeout, check=True, encoding='utf-8')


class TargetOJ(ABC):
    @abstractmethod
    def get_table(self) -> dict[str, dict[str, list[int | str]]]:
        pass

    @abstractmethod
    def get_code(self, submission_id: int | str) -> str:
        pass

    def __cyclin_request(self, err_msg: str, request: Callable[..., requests.Response], *args, **kwargs) -> requests.Response:
        while True:
            res = request(*args, **kwargs)
            if res.ok:
                return res
            yellow(f'{err_msg} {res.reason}, wait for 15s')
            sleep(15)


class NowCoder(TargetOJ):
    def __init__(self, contest_id: int | str, t: str):
        """
        t: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        """
        self.__CONTEST_ID = contest_id
        self.__t = t

    def get_table(self) -> dict[str, dict[str, list[int | str]]]:
        table_url = f'https://ac.nowcoder.com/acm-heavy/acm/contest/status-list?statusTypeFilter=5&id={self.__CONTEST_ID}&page='
        json = self.__cyclin_request(
            'get nowcoder all submission id', requests.get, table_url)
        page_cnt = json['data']['basicInfo']['pageCount']

        table = {}
        for i in range(page_cnt):
            cur_url = table_url + str(i + 1)
            json = requests.get(cur_url).json()
            for submission in json['data']['data']:
                lang = submission['languageCategoryName']
                if lang == 'C++':
                    lang = 'cpp'
                elif lang == 'Python3' or lang == 'PyPy3':
                    lang = 'py'
                else:
                    continue
                table.setdefault(submission['index'], {}).setdefault(
                    lang, []).append(submission['submissionId'])
        return table

    def get_code(self, submission_id: int | str) -> str:
        submission_url = f'https://ac.nowcoder.com/acm/contest/view-submission?submissionId={submission_id}'
        res = self.__cyclin_request(
            f'get nowcoder {submission_id} submission code', requests.get, submission_url, cookies={'t': self.__t})
        soup = BeautifulSoup(res.text, 'html.parser')
        return soup.find('pre').text


class Codeforces(TargetOJ):
    def __init__(self, contest_id: int | str, csrf_token: str, jsession_id: str):
        """
        csrf_token: 按 F12 打开开发者工具，选择网络->打开一个提交->找到 submitSource 包 -> 负载

        jsession_id: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        """
        self.__CONTEST_ID = contest_id
        self.__CSRF_TOKEN = csrf_token
        self.__JSESSION_ID = jsession_id

    def get_table(self) -> dict[str, dict[str, list[int | str]]]:
        table_url = f'https://codeforces.com/api/contest.status?contestId={self.__CONTEST_ID}'
        json = self.__cyclin_request(
            'get codeforces all submission id', requests.get, table_url).json()

        table = {}
        for submission in json['result']:
            if 'verdict' not in submission or submission['verdict'] != 'OK':
                continue

            lang: str = submission['programmingLanguage']
            if lang.startswith('C++'):
                lang = 'cpp'
            elif lang.startswith(('Python', 'PyPy')):
                lang = 'py'
            else:
                continue

            table.setdefault(submission['problem']['index'], {}).setdefault(
                lang, []).append(submission['id'])
        return table

    def get_code(self, submission_id: int | str) -> str:
        submission_url = f'https://codeforces.com/data/submitSource?submissionId={submission_id}'
        header = {
            'Referer': f'https://codeforces.com/contest/{self.__CONTEST_ID}/status',
            'X-Csrf-Token': self.__CSRF_TOKEN,
            'cookie': f'JSESSIONID={self.__JSESSION_ID}',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0',
        }
        res = self.__cyclin_request(
            f'get codeforces {submission_id} submission code', requests.post, submission_url, headers=header).json()
        return res['source']


class HackAM:
    def __init__(self, target_oj: TargetOJ, base_dir: str | Path = 'code', thread_count: int = cpu_count() - 3):
        self.__TARGET_OJ = target_oj
        self.__BASE_DIR: Path = Path(base_dir)
        self.__THREAD_COUNT: int = thread_count
        self.__HACKED_LOG: Path = self.__BASE_DIR / 'hack.log'

    def __del__(self):
        self.clear_exe()

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

    def __get_typed_path(self, dir: Path, name: str | Path) -> Path:
        path: Path = dir / (name + '.cpp')
        if not path.exists():
            path = path.with_suffix('.py')
            if not path.exists():
                return None
        return path

    def __hacked_flag_wrap(self, hacked_flag: Path):
        return lambda fut: hacked_flag.touch()

    def pull_and_hack(self):
        self.__BASE_DIR.mkdir(exist_ok=True)
        with ThreadPoolExecutor(self.__THREAD_COUNT) as executor, self.__HACKED_LOG.open('w+', encoding='utf-8') as log:
            res: list[Future] = []
            for problem_id, sub_dict in self.__TARGET_OJ.get_table().items():
                problem_dir: Path = self.__BASE_DIR / problem_id
                problem_dir.mkdir(exist_ok=True)

                input_file = self.__get_typed_path(problem_dir, 'input')
                if input_file is None:
                    yellow(
                        f'No input files for {problem_dir.name}, skipping...')
                    continue

                std_file = self.__get_typed_path(problem_dir, 'std')
                if std_file is None:
                    yellow(
                        f'No std files for {problem_dir.name}, skipping...')
                    continue

                input_file: Run = Run(input_file)
                std_file: Run = Run(std_file)

                for lang, submission_ids in sub_dict.items():
                    lang_dir: Path = problem_dir / lang
                    lang_dir.mkdir(exist_ok=True)

                    for sub_id in submission_ids:
                        hacked_dir: Path = lang_dir / str(sub_id)
                        hacked_file: Path = hacked_dir / f'hacked.{lang}'
                        hacked_flag: Path = hacked_dir / 'hacked'

                        hacked_dir.mkdir(exist_ok=True)
                        if hacked_flag.exists():
                            continue

                        with hacked_file.open('w', encoding='utf-8') as f:
                            f.write(self.__TARGET_OJ.get_code(sub_id))

                        hacked_file: Run = Run(hacked_file)

                        fut = executor.submit(
                            self.__run_hack, input_file, std_file, hacked_file, hacked_dir, log)
                        fut.add_done_callback(
                            self.__hacked_flag_wrap(hacked_flag))
                        res.append(fut)

                        sleep(5)

            wait(res)

    def clear_hacked_files(self):
        self.__HACKED_LOG.unlink(True)
        for x_path in self.__BASE_DIR.iterdir():
            for dirs in x_path.iterdir():
                if dirs.is_dir():
                    shutil.rmtree(dirs)

    def clear_hacked_flags(self):
        self.__HACKED_LOG.unlink(True)
        for hacked_flag in self.__BASE_DIR.rglob('hacked'):
            hacked_flag.unlink()

    def clear_exe(self):
        for exe in self.__BASE_DIR.rglob('*.exe'):
            exe.unlink()


if __name__ == '__main__':
    target_oj = Codeforces(
        1979, '3251904c450e2cb5aa111d1ad88e988a', '786BA1B9273A5AD099CF14AFB123E29D')
    am = HackAM(target_oj, 'cf')

    # target_oj = NowCoder(82707, 'CA5B58A7304EC58A2445946E960293A0')
    am = HackAM(target_oj)
    am.pull_and_hack()
