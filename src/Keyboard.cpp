//
// Created by reichsstolz on 02.10.2021.
//

#include <QGridLayout>
#include "Keyboard.hpp"

Keyboard::Keyboard(QWidget *parent) : QWidget((parent)) {
    QPushButton *left_button = new QPushButton("<-", this);
    QPushButton *right_button = new QPushButton("->", this);
    QPushButton *up_button = new QPushButton("up", this);
    QPushButton *bot_button = new QPushButton("down", this);
    QPushButton *left_point_button = new QPushButton(".", this);
    QPushButton *right_point_button = new QPushButton(".", this);

    left_button->setMinimumSize(200, 50);
    right_button->setMinimumSize(200, 50);
    up_button->setMinimumSize(200, 50);
    bot_button->setMinimumSize(200, 50);
    left_point_button->setMinimumSize(200, 50);
    right_point_button->setMinimumSize(200, 50);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(left_button, 0, 0);
    grid->addWidget(right_button, 0, 2);
    grid->addWidget(up_button, 0, 1);
    grid->addWidget(left_point_button, 1, 0);
    grid->addWidget(right_point_button, 1, 2);
    grid->addWidget(bot_button, 1, 1);

    grid->setSpacing(0);
    grid->setVerticalSpacing(0);

    setLayout(grid);

}

