from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.options import Options
from termcolor import colored
import os


# 准备工作：
# 1. 将 chromedriver.exe 的路径添加到环境变量。 C:\Program Files\Google\Chrome\Application
# 2. 找到 chrome profile 路径。 "C:\Users\21396\AppData\Local\Google\Chrome\User Data"
#
# 手动操作：
# 1. 命令行输入以下命令打开 Google
# chrome --remote-debugging-port=9222 --user-data-dir=<chrome profile 路径>
# 3. 在浏览器中打开提交页面，选择题号，选择状态 "答案正确"。
# 4. 复制网页链接，传给下面程序


def get_driver():
    # 设置Chrome选项
    options = Options()
    options.add_experimental_option("debuggerAddress", "localhost:9222")
    options.add_argument(
        "user-data-dir=C:\\Users\\21396\\AppData\\Local\\Google\\Chrome\\User Data")

    # 连接到已经打开的Chrome实例
    driver = webdriver.Chrome(options=options)
    return driver


class NowCoder():
    def __init__(self, driver) -> None:
        self.driver = driver

    def find_element_by_XPath(self, XPath):
        code_element = None
        try:
            WebDriverWait(self.driver, 10).until(
                EC.presence_of_element_located((By.XPATH, XPath))
            )
            code_element = self.driver.find_element(By.XPATH, XPath)
        finally:
            assert code_element
            return code_element

    def get_submission_code(self, submissionId):
        # 转到特定的代码提交页面
        url = f'https://ac.nowcoder.com/acm/contest/view-submission?submissionId={submissionId}'
        self.driver.get(url)

        # 提取题号
        problem_id_XPath = '/html/body/div/div[2]/div[1]/a[2]'
        problem_id = self.find_element_by_XPath(
            problem_id_XPath).text.split()[0]

        # 提取运行状态
        run_status_XPath = '/html/body/div/div[2]/div[2]/div[2]/div[1]/div/span[6]'
        run_status = self.find_element_by_XPath(run_status_XPath).text

        # 提取语言
        used_language_XPath = '/html/body/div/div[2]/div[2]/div[2]/div[1]/div/span[2]'
        lang_expr = self.find_element_by_XPath(used_language_XPath).text
        if lang_expr.find('C++') != -1:
            language = 'cpp'
        elif lang_expr.find('pypy3') != -1 or lang_expr.find('Python3') != -1:
            language = 'py'
        else:
            language = 'other'

        # 提取代码
        code_XPath = '/html/body/div/div[2]/div[2]/div[2]/div[2]/div/div/div[2]/table/tbody/tr/td[2]'
        code_text = self.find_element_by_XPath(code_XPath).text

        # 作者信息
        auther_XPath = '/html/body/div/div[2]/div[2]/div[2]/div[1]/h2/a'
        auther = self.find_element_by_XPath(auther_XPath).text
        print(
            f'Successfully! author = {colored(auther, "magenta")}, submissionId = {submissionId}, problem_id = {colored(problem_id, "blue")}, run_status = {colored(run_status, "green")}'
        )
        return problem_id, code_text, language, run_status

    def get_submissionId(self, url):
        self.driver.get(url)
        submission_table_XPath = '/html/body/div[1]/div[4]/div[2]/div[2]/table/tbody'
        table = self.find_element_by_XPath(submission_table_XPath)
        rows = table.find_elements(By.TAG_NAME, 'tr')
        return list(row.text.split()[0] for row in rows)


if __name__ == '__main__':
    now = NowCoder(get_driver())
    # 修改 url
    url = 'https://ac.nowcoder.com/acm/contest/82707#submit/%22statusTypeFilter%22%3A%225%22%2C%22page%22%3A1'

    for page in range(1, 8 + 1):  # 修改 page 得到所有代码
        url = url[:len(url)-1]+str(i)
        ids = now.get_submissionId(url)
        for i in ids:
            problem_id, code_text, lang, run_status = now.get_submission_code(
                i)
            lang_path = './submission/' + problem_id + '/' + lang
            if not os.path.exists(lang_path):
                os.makedirs(lang_path)
            filename = lang_path + '/' + i + '.' + lang
            with open(filename, 'w', encoding='utf-8') as file:
                file.write(code_text)
            print('代码已保存到 ' + filename)
