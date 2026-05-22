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

#ifndef AWESOME_MAINWINDOW_HPP
#define AWESOME_MAINWINDOW_HPP

#include <memory>
#include <QWidget>

QT_BEGIN_NAMESPACE

/** 前向声明
 * 告诉编译器：在 Ui 命名空间中，有一个 mainwindow 的类。
 * 此类不是窗口类，而是 UIC 根据 mainwindow.ui 自动生成
 * 的界面类。
 * 这种方式无需引入ui_mainwindow.h，减少头文件依赖，加快
 * 编译速度。
 */
namespace Ui {
    class mainwindow;
}

QT_END_NAMESPACE

namespace basic::calculator {
    class engine;
}

namespace basic::widgets {

    /** 定义窗口类 */
    class mainwindow : public QWidget {
        Q_OBJECT /** 启用元对象 */

    public:
        /** 默认无父对象，即创建一个顶层窗口 */
        explicit
        mainwindow(QWidget* parent = nullptr);

        ~mainwindow() override;

    private:
        auto
        bind_calculator_buttons() -> void;

        auto
        refresh_display() const -> void;

        /**< 指向界面类的指针 */
        Ui::mainwindow* ui;

        /**< 无法采用按值引用，MOC 对C++20/23 modules 的支持有限 */
        std::unique_ptr<basic::calculator::engine> calculator_;
    };
}


#endif //AWESOME_MAINWINDOW_HPP
