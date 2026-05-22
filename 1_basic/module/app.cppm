// Copyright (C) 2026 Aaron <communicate_aaron@outlook.com>
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

module;
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include "../ui/mainwindow.hpp"
export module app;

export
int
run_app(int argc, char* argv[]) {
    QApplication app(argc, argv);

    /** 1. 显示文本：确定能运行 Qt 代码 */
    // QLabel label("Hello, qt 6!");
    // label.resize(400, 300);
    // label.show();

    /** 2. 显示图片：测试RCC */
    // QLabel label;
    // label.setPixmap(QPixmap(":/resources/images/1.png"));
    // label.show();

    /** 3. 展示.ui文件：测试UIC
     * 需要注意到这里与示例代码不同，因为我引用的是
     * mainwindow.hpp文件，而不是mainwindow.ui文件。
     * 当然如果非要按照示例代码，这需在CMakeLists中插入
     * set_property(TARGET 1_basics
     *       PROPERTY AUTOUIC_SEARCH_PATHS
     *       "${CMAKE_CURRENT_SOURCE_DIR}/ui")
     * 前者相对于后者调用关系更干净。
     */
    // mainwindow w;
    // w.show();

    /** 4. 练习：计算机 */
    basic::widgets::mainwindow w;
    w.show();

    return app.exec();
}
