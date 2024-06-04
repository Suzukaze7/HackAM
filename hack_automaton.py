from abc import ABC, abstractmethod
from io import TextIOWrapper
import shutil
from string import ascii_uppercase
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
            subprocess.run(['g++', '-std=c++17', self.__src, '-o', self.__dst])
            self.__is_cpp = True
        else:
            self.__dst = self.__src
            self.__is_cpp = False

    def __del__(self):
        if self.__is_cpp:
            self.__dst.unlink()

    def __str__(self):
        return str(self.__src)

    def run(self, stdin=None, stdout=None, timeout=None) -> subprocess.CompletedProcess:
        if self.__is_cpp:
            return subprocess.run(self.__dst, stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')
        else:
            return subprocess.run(['python', self.__dst], stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')


class TargetOJ(ABC):
    @abstractmethod
    def get_table(self) -> dict[str, dict[str, list[int | str]]]:
        pass

    @abstractmethod
    def get_code(submission_id: int | str) -> str:
        pass


class NowCoder(TargetOJ):
    def __init__(self, contest_id: int | str, t: str):
        """
        t: 在 cookie 中，可以浏览器 url 左边，也可以在 F12 中找
        """
        self.__CONTEST_ID = contest_id
        self.__t = t

    def get_table(self) -> dict[str, dict[str, list[int | str]]]:
        table_url = f'https://ac.nowcoder.com/acm-heavy/acm/contest/status-list?statusTypeFilter=5&id={self.__CONTEST_ID}&page='
        json = get(table_url).json()
        page_cnt = json['data']['basicInfo']['pageCount']

        table = {}
        for i in range(page_cnt):
            cur_url = table_url + str(i + 1)
            json = get(cur_url).json()
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
        res = get(submission_url, cookies={'t': self.__t})
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
        json = get(table_url).json()

        submissions = {}
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

            submissions.setdefault(submission['problem']['index'], {}).setdefault(
                lang, []).append(submission['id'])
        return submissions

    def get_code(self, submission_id: int | str) -> str:
        submission_url = f'https://codeforces.com/data/submitSource?submissionId={submission_id}'
        header = {
            'Referer': f'https://codeforces.com/contest/{self.__CONTEST_ID}/status',
            'X-Csrf-Token': self.__CSRF_TOKEN,
            'cookie': f'JSESSIONID={self.__JSESSION_ID}',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36 Edg/125.0.0.0',
        }
        res = post(submission_url, headers=header).json()
        return res['source']


class HackAM:
    def __init__(self, target_oj: TargetOJ, base_dir: str | Path = 'code', thread_count: int = cpu_count() - 3):
        self.__TARGET_OJ = target_oj
        self.__BASE_DIR: Path = Path(base_dir)
        self.__THREAD_COUNT: int = thread_count
        self.__HACKED_LOG: Path = self.__BASE_DIR / 'hacked.log'

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

    def __get_typed_path(self, dir: Path, name: str | Path) -> Path:
        path = (dir / name).with_suffix('.cpp')
        if not path.exists():
            path = path.with_suffix('.py')
            if not path.exists():
                return None
        return path

    def pull_and_hack(self):
        self.__BASE_DIR.mkdir(exist_ok=True)
        with ThreadPoolExecutor(self.__THREAD_COUNT) as executor, self.__HACKED_LOG.open('w+', encoding='utf-8') as log:
            res: list[Future] = []
            for problem_id, sub_dict in self.__TARGET_OJ.get_table().items():
                problem_dir: Path = self.__BASE_DIR / problem_id
                problem_dir.mkdir(exist_ok=True)

                input_file = self.__get_typed_path(problem_dir, 'input')
                if not input_file:
                    self.__yellow(
                        f'No input files for {problem_dir.name}, skipping...')
                    continue

                std_file = self.__get_typed_path(problem_dir, 'std')
                if not std_file:
                    self.__yellow(
                        f'No std files for {problem_dir.name}, skipping...')
                    continue

                input_file: Run = Run(input_file)
                std_file: Run = Run(std_file)

                for lang, submission_ids in sub_dict.items():
                    lang_dir: Path = problem_dir / lang
                    lang_dir.mkdir(exist_ok=True)

                    for sub_id in submission_ids:
                        hacked_dir: Path = lang_dir / sub_id
                        hacked_file: Path = hacked_dir / f'hacked.{lang}'
                        hacked_flag: Path = lang_dir / 'hacked'

                        hacked_dir.mkdir(exist_ok=True, parents=True)
                        if hacked_flag.exists():
                            continue

                        with hacked_file.open('w', encoding='utf-8') as f:
                            f.write(self.__TARGET_OJ.get_code(sub_id))

                        hacked_file: Run = Run(hacked_file)

                        fut = executor.submit(
                            self.__run_hack, input_file, std_file, hacked_file, hacked_dir, log)
                        fut.add_done_callback(lambda: hacked_flag.touch())
                        res.append(fut)

                        sleep(10)

            wait(res)

    def clear_hacked_files(self):
        self.__HACKED_LOG.unlink(True)
        for x_path in self.__BASE_DIR.iterdir():
            for dirs in x_path.iterdir():
                if dirs.is_dir():
                    shutil.rmtree(dirs)


if __name__ == '__main__':
    target_oj = Codeforces(
        1980, '3251904c450e2cb5aa111d1ad88e988a', '786BA1B9273A5AD099CF14AFB123E29D')
    am = HackAM(target_oj, 'cf')
