from pathlib import Path


def list_files(directory):
    li = []
    path = Path(directory)
    for filepath in path.rglob('*'):
        if filepath.is_file() and filepath.suffix != '.other':
            li.append(filepath)
    return li


li = list_files('./submission')
for filepath in li:
    dirpath = Path('input_and_std') / filepath.parent.parent.relative_to(filepath.parts[0]
                                                                         )
    if not Path.exists(dirpath):
        Path.mkdir(dirpath)
        print(f'mkdir {dirpath}')
