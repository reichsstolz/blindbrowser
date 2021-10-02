//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_WINDOW_H
#define BLINDBROWSER_WINDOW_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>


// https://ravesli.com/urok-6-osnovy-raboty-s-gui-v-qt5/
// файл главного окна
#include "Keyboard.hpp"
class Window {
private:
    //Keyboard box; объект клавиатуры

    //void InputMode();  // наш телефон будет работать в режиме ввода, когда пользователь будет вводить данные

public:
    void InitUI();  // инициализация интерфейса
};


#endif //BLINDBROWSER_WINDOW_H
