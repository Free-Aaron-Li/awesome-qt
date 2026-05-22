# 1. Qt 自动编译三件套
# 1.1 MOC（Meta-Object Compiler），自动运行处理信号槽机制
set(CMAKE_AUTOMOC ON)
# 1.2 RCC（Resource Compiler），自动处理资源管理
set(CMAKE_AUTORCC ON)
# 1.3 UIC（User Interface Compiler），自动转化.ui文件
set(CMAKE_AUTOUIC ON)

# 2. 创建可执行目标
add_executable(1_basics
               src/main.cpp
               resources.qrc
               ui/mainwindow.cpp
               ui/mainwindow.hpp
               ui/mainwindow.ui
               module/calculator.cppm
)

# 3. 为目标添加 C++20 模块源文件
# PRIVATE: 模块文件仅对当前目标可见
# FILE_SET cxx_modules TYPE CXX_MODULES: 定义文件集类型为 C++ 模块
target_sources(1_basics
               PRIVATE
               FILE_SET cxx_modules TYPE CXX_MODULES
               FILES
               module/app.cppm
               module/calculator.cppm
)

# 4.寻找模块
# find_package: 查找并加载 Qt6 库及其指定组件
# COMPONENTS: 关键字，后面列出需要的具体组件
#   Core: Qt 核心模块，提供基础的非 GUI 功能（如信号槽、对象模型、容器类等）
#   Gui: Qt GUI 模块，提供 GUI 相关的基础类（如窗口、图形、字体等）
#   Widgets: Qt Widgets 模块，提供传统的桌面 UI 控件（如按钮、标签、对话框等）
# REQUIRED: 如果找不到这些组件，CMake 会停止配置并报错
find_package(Qt6 COMPONENTS
             Core
             Gui
             Widgets
             REQUIRED)

# target_link_libraries: 为目标链接所需的库
target_link_libraries(1_basics
                      Qt::Core
                      Qt::Gui
                      Qt::Widgets
)

# 5.为目标添加编译选项
# PRIVATE: 这些编译选项仅应用于当前目标，不会传递给依赖此目标的其他目标
# -Wall: 启用所有常用警告
# -Wextra: 启用额外的警告信息
# -Wpedantic: 严格遵循 C++ 标准，对不符合标准的代码发出警告
target_compile_options(1_basics
                       PRIVATE
                       -Wall
                       -Wextra
                       -Wpedantic
)
