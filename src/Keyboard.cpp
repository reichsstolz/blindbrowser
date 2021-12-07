// Copyright 2021 Tinkerrer

#include <QGridLayout>
#include "Keyboard.hpp"
#include "moc_Keyboard.cpp"

#include <string>

Keyboard::Keyboard(QWidget *parent) : QWidget((parent)) {
    //создание кнопок
    for (auto& button: keyboard_buttons) {
        button = new QPushButton(this);
        button->setMinimumSize(200, 50);
        button->setFont(QFont("Purisa", 15));
    }

    //установка кнопок в сетку
    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(keyboard_buttons[0], 0, 0);
    grid->addWidget(keyboard_buttons[3], 0, 1);
    grid->addWidget(keyboard_buttons[1], 1, 0);
    grid->addWidget(keyboard_buttons[4], 1, 1);
    grid->addWidget(keyboard_buttons[2], 2, 0);
    grid->addWidget(keyboard_buttons[5], 2, 1);

    //устанавливаем функций кнопок и текст на них
    ReturnButtonsFunctions();

    //установка расстояний между кнопками в сетке
    grid->setSpacing(0);
    grid->setVerticalSpacing(0);
    setLayout(grid);
}

void Keyboard::BlockAllButtons() {
    for (auto& button: keyboard_buttons) {
        button->blockSignals(true);
    }
}

void Keyboard::UnblockAllButtons() {
    for (auto& button: keyboard_buttons) {
        button->blockSignals(false);
    }
}

void Keyboard::ReturnButtonsFunctions() {
    //установка текста
    keyboard_buttons[0]->setText("<-");
    keyboard_buttons[3]->setText("->");
    keyboard_buttons[1]->setText("up");
    keyboard_buttons[4]->setText("down");
    keyboard_buttons[2]->setText(".");
    keyboard_buttons[5]->setText(".");

    //функция, скролящиая страницу
    connect(keyboard_buttons[1], &QPushButton::clicked, this, [this]() {
        emit Scroll("up");
    });
    connect(keyboard_buttons[4], &QPushButton::clicked, this, [this]() {
        emit Scroll("down");
    });

    //функция, реализующая переход к предыдущей или последующей странице
    connect(keyboard_buttons[0], &QPushButton::clicked, this, [this]() {
        emit ForwardBackward("backward");
    });
    connect(keyboard_buttons[3], &QPushButton::clicked, this, [this]() {
        emit ForwardBackward("forward");
    });
}

void Keyboard::OpenInputMode() {
    BlockAllButtons();
    for (auto& button: keyboard_buttons) {
        button->setText("");
        //удаляет все предыдущие зависимости кнопок, <-, ->, up, down and etc
        disconnect(button, &QPushButton::clicked, nullptr, nullptr);
    }
}

void Keyboard::CloseInputMode() {
    for (auto& button: keyboard_buttons) {
        disconnect(button, &QPushButton::clicked, nullptr, nullptr);
    }

    //возвращаем предыдущие зависимости основных кнопок
    ReturnButtonsFunctions();

    UnblockAllButtons();
}

void Keyboard::InputSymbol(size_t row, size_t column) {
    UnblockAllButtons();

    //вводимое значение по умолчанию - пробел
    input_value = "000000:";

    for (size_t i = 0; i < 6; ++i) {
        //отключает предыдущие функции, за которые отвечали кнопки Keyboard, чистит текст в них
        keyboard_buttons[i]->setText("");
        disconnect(keyboard_buttons[i], nullptr, nullptr, nullptr);

        //устанавливает функции ввода для новых кнопок
        connect(keyboard_buttons[i], &QPushButton::clicked, this, [=] {
            //если эта кнопка уже была нажата, то ввод заканчивается
            if (input_value[i] == '1') {
                BlockAllButtons();
                //для очастки символа символа необходимо нажать на все кнопки
                if (input_value == "111111:") {
                    input_value = "000000:";
                }
                emit EnteredSymbol(input_value, row, column);
            } else {
                input_value[i] = '1';
                keyboard_buttons[i]->setText(".");
            }
        });
    }
}

