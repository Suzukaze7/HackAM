import shutil
import subprocess
from concurrent.futures import ThreadPoolExecutor, wait
from multiprocessing import cpu_count
from pathlib import Path
from requests import get
from bs4 import BeautifulSoup
from func_timeout import FunctionTimedOut, func_set_timeout

THREAD_COUNT = max(1, cpu_count() // 2)
base_dir = Path('code')


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
            self.__dst.unlink(True)

    def __str__(self):
        return str(self.__src)

    def run(self, stdin=None, stdout=None, timeout=None) -> subprocess.CompletedProcess:
        if self.__is_cpp:
            return subprocess.run(self.__dst, stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')
        else:
            return subprocess.run(['python', self.__dst], stdin=stdin, stdout=stdout, timeout=timeout, check=True, encoding='utf-8')


def red(s):
    print('\033[91m', s, '\033[0m', sep='')


def green(s):
    print('\033[32m', s, '\033[0m', sep='')


def yellow(s):
    print('\033[33m', s, '\033[0m', sep='')


def NowCoder(contest_id: int | str, cookie: str):
    table_url = f'https://ac.nowcoder.com/acm-heavy/acm/contest/status-list?statusTypeFilter=5&id={contest_id}&page='
    js = get(table_url).json()
    page_cnt = js['data']['basicInfo']['pageCount']

    submissions = {}
    for i in range(page_cnt):
        cur_url = table_url + str(i + 1)
        js = get(cur_url).json()
        for sub in js['data']['data']:
            lang = sub['languageCategoryName']
            if lang == 'C++':
                lang = 'cpp'
            elif lang == 'Python3' or lang == 'PyPy3':
                lang = 'py'
            else:
                lang = 'other'
            submissions.setdefault((sub['index'], lang), []).append(
                str(sub['submissionId']))

    base_dir.mkdir(exist_ok=True)

    def crawler(hacked_dir: Path):
        hacked_dir.mkdir(exist_ok=True)

        submission_url = 'https://ac.nowcoder.com/acm/contest/view-submission?submissionId=' + hacked_dir.name
        res = get(submission_url, cookies={'t': cookie})
        soup = BeautifulSoup(res.text, 'html.parser')

        with (hacked_dir / f'hacked.{hacked_dir.parent.name}').open('w', encoding='utf-8') as f:
            f.write(soup.find('pre').text)

    with ThreadPoolExecutor(THREAD_COUNT) as executor:
        res = []
        for types, ids in submissions.items():
            problem, lang = types
            lang_dir: Path = base_dir / problem / lang
            lang_dir.mkdir(parents=True, exist_ok=True)
            for id in ids:
                res.append(executor.submit(crawler, lang_dir / id))
        wait(res)


@func_set_timeout(30)
def start_hack(input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path):
    in_file = hacked_dir / "1.in"
    out_file = hacked_dir / "1.out"
    res_file = hacked_dir / "1.result"
    while True:
        input_file.run(stdout=in_file.open(
            'w', encoding='utf-8')).check_returncode()

        std_file.run(in_file.open('r', encoding='utf-8'),
                     out_file.open("w", encoding='utf-8')).check_returncode()

        hacked_file.run(in_file.open('r', encoding='utf-8'),
                        res_file.open("w", encoding='utf-8')).check_returncode()

        with out_file.open("r", encoding='utf-8') as f:
            out = [line.strip() for line in f.readlines()]
        with res_file.open("r", encoding='utf-8') as f:
            result = [line.strip() for line in f.readlines()]

        if out != result:
            break


def run_hack(input_file: Run, std_file: Run, hacked_file: Run, hacked_dir: Path):
    green(f'Hacking: {input_file} {std_file} {hacked_file}')
    try:
        start_hack(input_file, std_file, hacked_file, hacked_dir)
    except FunctionTimedOut:
        green(f"Accepted: {hacked_file}")
        for data in hacked_dir.glob('1.*'):
            data.unlink()
    except Exception as e:
        red(f'Error occurred: {hacked_file} {e}')
    else:
        red(f'Hack successfully: {hacked_file}')


def process_submissions():
    with ThreadPoolExecutor(THREAD_COUNT) as executor:
        res = []
        for x_path in base_dir.iterdir():
            # 尝试定义 input.cpp 文件路径
            input_file = x_path / "input.cpp"
            if not input_file.exists():
                input_file = x_path / "input.py"
                if not input_file.exists():
                    yellow(f"No input files for {x_path.name}, skipping...")
                    continue

            # 尝试定义 std.cpp 文件路径
            std_file = x_path / "std.cpp"
            if not std_file.exists():
                std_file = x_path / "std.py"
                if not std_file.exists():
                    yellow(f"No std files for {x_path.name}, skipping...")
                    continue

            input_file = Run(input_file)
            std_file = Run(std_file)

            # 遍历 cpp 目录, hack
            for lang in ("cpp", 'py'):
                type_dir = x_path / lang
                if not type_dir.exists():
                    continue
                for hacked_dir in type_dir.iterdir():
                    for hacked_file in hacked_dir.glob(f'*.{lang}'):
                        res.append(executor.submit(
                            run_hack, input_file, std_file, Run(hacked_file), hacked_dir))

        wait(res)


def rm_hacked_files():
    for x_path in base_dir.iterdir():
        for dirs in x_path.iterdir():
            if dirs.is_dir():
                shutil.rmtree(dirs)


def rm_exe():
    for exe in base_dir.rglob('*.exe'):
        exe.unlink()


if __name__ == "__main__":
    # NowCoder(82707, 'BD68172701F0DDCE982E12856DC560AB')
    process_submissions()
