//
// Created by reichsstolz on 02.10.2021.
//

#include <QGridLayout>
#include "Keyboard.hpp"
#include "moc_Keyboard.cpp"

Keyboard::Keyboard(QWidget *parent) : QWidget((parent)) {
    keyboard_buttons[0] = new QPushButton("<-", this);
    keyboard_buttons[3] = new QPushButton("->", this);
    keyboard_buttons[1] = new QPushButton("up", this);
    keyboard_buttons[4] = new QPushButton("down", this);
    keyboard_buttons[2] = new QPushButton(".", this);
    keyboard_buttons[5] = new QPushButton(".", this);

    for (size_t i = 0; i < 6; ++i) {
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
    keyboard_buttons[0]->setText("<-");
    keyboard_buttons[3]->setText("->");
    keyboard_buttons[1]->setText("up");
    keyboard_buttons[4]->setText("down");
    keyboard_buttons[2]->setText(".");
    keyboard_buttons[5]->setText(".");
}

void Keyboard::InputSymbol(size_t row, size_t colomn) {
    UnblockAllButtons();
    input_value = 0;
    for (size_t i = 0; i < 6; ++i) {
        keyboard_buttons[i]->setText("");
        //отключает предыдущие функции, за которые отвечали кнопки Kayboard
        disconnect(keyboard_buttons[i], nullptr, nullptr, nullptr);
        //устанавливает функции ввода для новых кнопок
        connect(keyboard_buttons[i], &QPushButton::clicked, this, [=] {
            //если эта точка уже была нажата, то ввод заканчивается
            if (input_value %  (1 << (6 - i)) / (1 << (5 - i))) {
                BlockAllButtons();
                emit EnteredSymbol(input_value, row, colomn);
            }
            else{
                input_value += (1 << (5 - i));
                keyboard_buttons[i]->setText(".");
            }
        });
    }
}

