//
// Created by reichsstolz on 02.10.2021.
//

#include <Window.hpp>

Window::Window(QWidget *parent) : QWidget(parent), keyboard_box(new Keyboard(this)), matrix_box(new MatrixWidget(this)) {
    //Setting title.
    setWindowTitle("BlindBrowser");
    //Making grid of Widgets
    auto *grid = new QGridLayout(this);
    //Adding matrix to grid of widgets
    grid->addWidget(matrix_box, 0, 0, Qt::AlignTop);
    //Adding keyboard to grid of widgets
    grid->addWidget(keyboard_box, 1, 0, Qt::AlignBottom);
    setLayout(grid); //setting grid

}

void Window::InitUI() {

}