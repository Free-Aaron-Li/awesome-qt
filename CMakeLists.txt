# 1. 指定 CMake 最低版本
cmake_minimum_required(VERSION 4.2)

# 2. 项目名称及使用到的语言
# 其中版本采用语义化版本号：MAJOR.MINOR.PATCH
project(awesome-qt VERSION 0.0.1 LANGUAGES C CXX)

# 3. 设置 C++ 标准
# 3.1 项目代码希望使用 C++23 编译
set(CMAKE_CXX_STANDARD 23)
# 3.2 必须支持该标准（C++20）
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 3.3 禁用编译器扩展
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. 确定可执行文件存放于顶层 bin/ 目录下
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/../bin)

# 5. 设定子项目（subproject）
add_subdirectory(1_basic)

