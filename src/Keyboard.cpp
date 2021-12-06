//
// Created by reichsstolz on 02.10.2021.
//

#include <QGridLayout>
#include "Keyboard.hpp"
#include "moc_Keyboard.cpp"

#include <string>

Keyboard::Keyboard(QWidget *parent) : QWidget((parent)) {
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i] = new QPushButton(this);
        keyboard_buttons[i]->setMinimumSize(200, 50);
        keyboard_buttons[i]->setFont(QFont("Purisa", 15));
    }

    QGridLayout *grid = new QGridLayout(this);

    grid->addWidget(keyboard_buttons[0], 0, 0);
    grid->addWidget(keyboard_buttons[3], 0, 1);
    grid->addWidget(keyboard_buttons[1], 1, 0);
    grid->addWidget(keyboard_buttons[4], 1, 1);
    grid->addWidget(keyboard_buttons[2], 2, 0);
    grid->addWidget(keyboard_buttons[5], 2, 1);

    //устанавливаем функции кнопок и текст на них
    ReturnButtonsFunctions();

    grid->setSpacing(0);
    grid->setVerticalSpacing(0);

    setLayout(grid);

}

void Keyboard::BlockAllButtons() {
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i]->blockSignals(true);
    }
}

void Keyboard::UnblockAllButtons() {
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i]->blockSignals(false);
    }
}

void Keyboard::ReturnButtonsFunctions() {
    keyboard_buttons[0]->setText("<-");
    keyboard_buttons[3]->setText("->");
    keyboard_buttons[1]->setText("up");
    keyboard_buttons[4]->setText("down");
    keyboard_buttons[2]->setText(".");
    keyboard_buttons[5]->setText(".");

    //функция, скролящие страницу
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
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i]->setText("");
        //disconnect the previous connections, <-, ->, up, down and etc
        disconnect(keyboard_buttons[i], nullptr, nullptr, nullptr);
    }
}

void Keyboard::CloseInputMode() {
    for (size_t i = 0; i < 6; ++i) {
        disconnect(keyboard_buttons[i], nullptr, nullptr, nullptr);
    }

    ReturnButtonsFunctions();

    UnblockAllButtons();
}

void Keyboard::InputSymbol(size_t row, size_t column) {
    UnblockAllButtons();
    input_value = "000000:";
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i]->setText("");
        //отключает предыдущие функции, за которые отвечали кнопки Keyboard
        disconnect(keyboard_buttons[i], nullptr, nullptr, nullptr);
        //устанавливает функции ввода для новых кнопок
        connect(keyboard_buttons[i], &QPushButton::clicked, this, [=] {
            //если эта точка уже была нажата, то ввод заканчивается
            if (input_value[i] == '1') {
                BlockAllButtons();
                //для очастки символа символа необходимо нажать на все точки
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

