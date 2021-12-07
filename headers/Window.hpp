// Copyright 2021 Tinkerrer

#ifndef BLINDBROWSER_WINDOW_H
#define BLINDBROWSER_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

#include "Keyboard.hpp"
#include "MatrixWidget.hpp"
#include "AddressBar.hpp"

class Window : public QWidget {
private:
    //указатель на виджет адресной строки
    AddressBar *address_bar;
    //указатель на виджет клавиатуры
    Keyboard *keyboard_box;
    //указатель на дисплей
    MatrixWidget *matrix_box;

public:
    explicit Window(QWidget *parent = nullptr);
};


#endif //BLINDBROWSER_WINDOW_H
