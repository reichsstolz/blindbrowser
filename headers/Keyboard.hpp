//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_BUTTONS_H
#define BLINDBROWSER_BUTTONS_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>


class Keyboard : public QWidget {

private:

public:
    explicit Keyboard(QWidget *parent = nullptr);

    ~Keyboard() override = default;
};


#endif //BLINDBROWSER_BUTTONS_H
