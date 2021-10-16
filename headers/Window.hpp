//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_WINDOW_H
#define BLINDBROWSER_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

// https://ravesli.com/urok-6-osnovy-raboty-s-gui-v-qt5/
// файл главного окна
#include "Keyboard.hpp"
#include "MatrixWidget.hpp"
#include "AddressBar.h"

class Window : public QWidget {
private:
    AddressBar *adress_bar; //указатель на виджет адресной строку
    Keyboard *keyboard_box; //указатель на виджет клавиатуры
    MatrixWidget *matrix_box; //указатель на дисплей

    //void InputMode();  // наш телефон будет работать в режиме ввода, когда пользователь будет вводить данные

public:
    explicit Window(QWidget *parent = nullptr);
};


#endif //BLINDBROWSER_WINDOW_H
