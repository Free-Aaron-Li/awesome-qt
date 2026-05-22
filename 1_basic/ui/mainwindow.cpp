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

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QString>
import calculator;

namespace basic::widgets {
    mainwindow::mainwindow(QWidget* parent) :
        QWidget(parent), ui(new Ui::mainwindow),
        calculator_(std::make_unique<basic::calculator::engine>()) {
        ui->setupUi(this);
        bind_calculator_buttons();
        refresh_display();
    }

    mainwindow::~mainwindow() { delete ui; }

    auto
    mainwindow::bind_calculator_buttons() -> void {
        connect(ui->button_0, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(0);
            refresh_display();
        });
        connect(ui->button_1, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(1);
            refresh_display();
        });
        connect(ui->button_2, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(2);
            refresh_display();
        });
        connect(ui->button_3, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(3);
            refresh_display();
        });
        connect(ui->button_4, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(4);
            refresh_display();
        });
        connect(ui->button_5, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(5);
            refresh_display();
        });
        connect(ui->button_6, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(6);
            refresh_display();
        });
        connect(ui->button_7, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(7);
            refresh_display();
        });
        connect(ui->button_8, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(8);
            refresh_display();
        });
        connect(ui->button_9, &QPushButton::clicked, this, [this] {
            calculator_->input_digit(9);
            refresh_display();
        });
        connect(ui->button_dot, &QPushButton::clicked, this, [this] {
            calculator_->input_dot();
            refresh_display();
        });
        connect(ui->button_add, &QPushButton::clicked, this, [this] {
            calculator_->set_operation(
                    basic::calculator::operation::add);
            refresh_display();
        });
        connect(ui->button_sub, &QPushButton::clicked, this, [this] {
            calculator_->set_operation(
                    basic::calculator::operation::subtract);
            refresh_display();
        });
        connect(ui->button_mul, &QPushButton::clicked, this, [this] {
            calculator_->set_operation(
                    basic::calculator::operation::multiply);
            refresh_display();
        });
        connect(ui->button_div, &QPushButton::clicked, this, [this] {
            calculator_->set_operation(
                    basic::calculator::operation::divide);
            refresh_display();
        });
        connect(ui->button_equal, &QPushButton::clicked, this, [this] {
            calculator_->calculate();
            refresh_display();
        });
        connect(ui->button_backspace, &QPushButton::clicked, this, [this] {
            calculator_->backspace();
            refresh_display();
        });
        connect(ui->button_clean_all, &QPushButton::clicked, this, [this] {
            calculator_->clear_all();
            refresh_display();
        });
        connect(ui->button_percent, &QPushButton::clicked, this, [this] {
            calculator_->percent();
            refresh_display();
        });
        connect(ui->button_sign, &QPushButton::clicked, this, [this] {
            calculator_->toggle_sign();
            refresh_display();
        });
    }

    auto
    mainwindow::refresh_display() const -> void {
        ui->line_edit_display->setText(
                QString::fromStdString(calculator_->text()));
    }
}
