//
// Created by reichsstolz on 02.10.2021.
//

#include <Window.hpp>

Window::Window(QWidget *parent) : QWidget(parent), address_bar(new AddressBar(this)), keyboard_box(new Keyboard(this)),
                                  matrix_box(new MatrixWidget(this)) {
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

    //нажатие на кнопку скрола Keyboard скролит MatrixWidget
    connect(keyboard_box, &Keyboard::Scroll, matrix_box, &MatrixWidget::ChangeLocatorAndUpdate);

    //нажатие на кнопку перехода на страницу вперед/назад меняет страницу
    connect(keyboard_box, &Keyboard::ForwardBackward, address_bar, &AddressBar::GoToForwardBackwardPage);

    //нажатие на адресную строку открывает режим ввода для этой адресной строки, повторно нажатие закрывает этот режим
    connect(address_bar, &QPushButton::clicked, matrix_box, [&] {
        if (address_bar->isCheckable()) {
            address_bar->setCheckable(false);
            keyboard_box->CloseInputMode();
            matrix_box->CloseInputMode();
            address_bar->ProcessURL(matrix_box->GetEntered());
        } else {
            address_bar->setCheckable(true);
            keyboard_box->OpenInputMode();
            matrix_box->OpenInputMode(address_bar->GetCurrentURL());
        }
    });

    //получение от AdressBar нового домена означает, что необходимо перейти на другой сайт
    connect(address_bar, &AddressBar::OpenPage, matrix_box, &MatrixWidget::BuildPage);

    //нажатие на любую кнопку в MatrixWidget в режиме ввода запускает функцию ввода этого символа, в качестве параметров передает координаты кнопки
    connect(matrix_box, &MatrixWidget::ClickedAnyButton, keyboard_box, &Keyboard::InputSymbol);
    //окончание ввода символа устанавливает введенный символ в кнопку, в качестве параметров передает координаты кнопки и введенный символ в "формате size_t"
    connect(keyboard_box, &Keyboard::EnteredSymbol, matrix_box, &MatrixWidget::SetSymbol);
}
