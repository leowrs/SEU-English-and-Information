# Original Author: GitHub @leowrs (https://github.com/leowrs)
import os

def check_file_name(directory, file_name):
    for file in os.listdir(directory):
        if file == file_name:
            return True
    return False

directory = "X:\ZH0006"  # 替换为你想要检查的目录路径
file_name = "0001.rar"  # 替换为你想要核对的文件名

if check_file_name(directory, file_name):
    print("文件名存在于目录中。")
else:
    print("文件名不存在于目录中。")
