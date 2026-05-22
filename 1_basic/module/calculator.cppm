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

#include <cmath>
#include <string>

export module calculator;

export namespace basic::calculator {
    enum class operation {
        none,
        add,
        subtract,
        multiply,
        divide,
        modulo,
    };

    class engine {
    public:
        [[nodiscard]] auto
        text() const -> std::string {
            if (pending_operation_ != operation::none && !inputting_) {
                return value_to_text(stored_value_) + " " + operator_symbol(
                               pending_operation_);
            }
            return display_text_;
        }

        [[nodiscard]] auto
        has_error() const -> bool { return has_error_; }

        auto
        clear_all() -> void {
            display_text_      = "0";
            stored_value_      = 0.0;
            pending_operation_ = operation::none;
            inputting_         = false;
            has_error_         = false;
        }

        auto
        input_digit(const int digit) -> void {
            if (has_error_) clear_all();
            if (!inputting_) {
                display_text_ = std::to_string(digit);
                inputting_    = true;
                return;
            }
            if (display_text_ == "0") {
                display_text_ = std::to_string(digit);
                return;
            }
            if (display_text_ == "-0") {
                display_text_ = "-" + std::to_string(digit);
            }
            display_text_ += std::to_string(digit);
        }

        auto
        input_dot() -> void {
            if (has_error_) clear_all();
            if (!inputting_) {
                display_text_ = "0.";
                inputting_    = true;
                return;
            }
            /** string.contains() C++23 实现 */
            if (!display_text_.contains('.')) { display_text_ += "."; }
        }

        auto
        backspace() -> void {
            if (has_error_) clear_all();
            if (!inputting_) return;
            if (display_text_.size() <= 1) {
                display_text_ = "0";
                inputting_    = false;
                return;
            }
            if (display_text_.size() == 2 && display_text_.front() == '-') {
                display_text_ = "0";
                inputting_    = false;
                return;
            }
            display_text_.pop_back();

            if (display_text_.empty() || display_text_ == "-") {
                display_text_ = "0";
                inputting_    = false;
                return;
            }
        }

        auto
        toggle_sign() -> void {
            if (has_error_) clear_all();
            if (display_text_ == "0") return;
            if (display_text_.front() == '-') {
                display_text_.erase(display_text_.begin());
                return;
            }
            display_text_.insert(display_text_.begin(), '-');
        }

        auto
        percent() -> void {
            if (has_error_) return;
            set_operation(operation::modulo);
        }

        auto
        set_operation(const operation op) -> void {
            if (has_error_) return;
            if (pending_operation_ != operation::none && inputting_) {
                calculate();
            } else { stored_value_ = current_value(); }

            pending_operation_ = op;
            inputting_         = false;
        }

        auto
        calculate() -> void {
            if (has_error_) return;

            const auto right_value = current_value();
            auto       result      = stored_value_;

            switch (pending_operation_) {
                case operation::none: { return; }
                case operation::add: {
                    result = stored_value_ + right_value;
                    break;
                }
                case operation::subtract: {
                    result = stored_value_ - right_value;
                    break;
                }
                case operation::multiply: {
                    result = stored_value_ * right_value;
                    break;
                }
                case operation::divide: {
                    if (right_value == 0.0) {
                        display_text_ = "Error";
                        has_error_    = true;
                        inputting_    = false;
                        return;
                    }
                    result = stored_value_ / right_value;
                    break;
                }
                case operation::modulo: {
                    if (right_value == 0.0) {
                        display_text_ = "Error";
                        has_error_    = true;
                        inputting_    = false;
                        return;
                    }
                    result = std::fmod(stored_value_, right_value);
                }
                default: break;
            }

            set_display_value(result);
            stored_value_      = result;
            pending_operation_ = operation::none;
            inputting_         = false;
        }

    private:
        [[nodiscard]] static auto
        operator_symbol(const operation op) -> std::string {
            switch (op) {
                case operation::add: return "+";
                case operation::subtract: return "-";
                case operation::multiply: return "*";
                case operation::divide: return "/";
                case operation::modulo: return "%";
                case operation::none: return "";
            }
            return "";
        }

        [[nodiscard]] static auto
        value_to_text(const double value) -> std::string {
            auto text = std::to_string(value);
            /** 删除小数尾随多余的0 */
            while (text.contains('.') && text.back() == '0') {
                text.pop_back();
            }
            if (!text.empty() && text.back() == '.') { text.pop_back(); }
            if (text == "-0") { text = "0"; }
            return text;
        }

        [[nodiscard]] auto
        current_value() const -> double {
            if (display_text_ == "-" || display_text_ == "." || display_text_ ==
                "-.") { return 0.0; }
            return std::stod(display_text_); /** string to double */
        }

        auto
        set_display_value(const double value) -> void {
            display_text_ = value_to_text(value);
        }

    private:
        /**< 当前显示内容 */
        std::string display_text_{ "0" };
        /**< 上一个操作数 */
        double stored_value_{ 0.0 };
        /**< 等待执行的运算 */
        operation pending_operation_{ operation::none };
        /**< 当前是否正在输入数字 */
        bool inputting_{ false };
        /**< 时候出现错误 */
        bool has_error_{ false };
    };
}
