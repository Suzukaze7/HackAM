import subprocess
from pathlib import Path


def run_pyjudge(input_file, std_file, hack_file, data_dir):
    print('Hacking :', input_file, std_file, hack_file, data_dir)
    # 构建命令
    command = f"python pyjudge.py hack {hack_file} -g {input_file} -s {std_file} -d {data_dir}"
    try:
        # 启动进程
        process = subprocess.Popen(
            command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate(timeout=30)
    except subprocess.TimeoutExpired:
        print('\033[32m' + "Accepted." + '\033[42m' + '\033[0m')
    except subprocess.CalledProcessError as e:
        print('\033[91m' + f"Error occurred: {e}" + '\033[101m' + '\033[0m')
    else:
        print(
            '\033[91m' + f'Hack "{hack_file}" successfully!' + '\033[101m' + '\033[0m')


def process_submissions():
    base_dir = Path(".")
    for x_path in (base_dir / Path('submission')).iterdir():
        # 检查这个路径是否是一个目录
        if not x_path.is_dir():
            continue
        x = x_path.name

        # 尝试定义 input.cpp 文件路径
        input_cpp = base_dir / f"input_and_std/{x}/input.cpp"
        if not input_cpp.exists():
            input_py = base_dir / f"input_and_std/{x}/input.py"
            if not input_py.exists():
                print(f"No input files for {x}, skipping...")
                continue
            input_file = input_py
        else:
            input_file = input_cpp

        # 尝试定义 std.cpp 文件路径
        std_cpp = base_dir / f"input_and_std/{x}/std.cpp"
        if not std_cpp.exists():
            std_py = base_dir / f"input_and_std/{x}/std.py"
            if not std_py.exists():
                print(f"No std files for {x}, skipping...")
                continue
            std_file = std_py
        else:
            std_file = std_cpp

        # 遍历 cpp 目录, hack
        for cpp in ("cpp", "py"):
            cpp_dir = base_dir / f"submission/{x}/{cpp}"
            for file in cpp_dir.glob(f'*.{cpp}'):
                run_pyjudge(input_file, std_file, file,
                            std_file.parent/file.stem)


if __name__ == "__main__":
    process_submissions()
