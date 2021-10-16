//
// Created by reichsstolz on 02.10.2021.
//

#include <Window.hpp>

Window::Window(QWidget *parent) : QWidget(parent), address_bar(new AddressBar(this)) ,keyboard_box(new Keyboard(this)), matrix_box(new MatrixWidget(this)) {
    //Setting title.
    setWindowTitle("BlindBrowser");
    //Making grid of Widgets
    auto *grid = new QGridLayout(this);
    grid->addWidget(address_bar, 0, 0, Qt::AlignTop);
    //Adding matrix to grid of widgets
    grid->addWidget(matrix_box, 1, 0, Qt::AlignTop);
    //Adding keyboard to grid of widgets
    grid->addWidget(keyboard_box, 2, 0, Qt::AlignTop);
    setLayout(grid); //setting grid

    //connect(address_bar, &AddressBar::EditAddress, matrix_box, &MatrixWidget::OpenInputMode);
}
