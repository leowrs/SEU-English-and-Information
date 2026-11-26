// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

bool checkFileName(const std::string& directory, const std::string& fileName) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().filename() == fileName) {
            return true;
        }
    }
    return false;
}

int main() {
    std::string directory = "X:\ZH0006";  // 替换为你想要检查的目录路径
    std::string fileName = "0001.rar";  // 替换为你想要核对的文件名

    if (checkFileName(directory, fileName)) {
        std::cout << "文件名存在于目录中。\n";
    }
    else {
        std::cout << "文件名不存在于目录中。\n";
    }

    return 0;
}