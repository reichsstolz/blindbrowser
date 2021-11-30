//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_BUTTONS_H
#define BLINDBROWSER_BUTTONS_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <array>

class Keyboard : public QWidget {

private:
Q_OBJECT
    std::array<QPushButton *, 6> keyboard_buttons{}; //массив кнопок
public:
    explicit Keyboard(QWidget *parent = nullptr);

    ~Keyboard() override = default;

    void BlockAllButtons();

    void UnblockAllButtons();

public slots:

    //открывает режим ввода
    void OpenInputMode();

    //закрывает режим ввода
    void CloseInputMode();

    //функция ввода символа для определенной кнопки MatrixWidget
    void InputSymbol(size_t row, size_t column);

signals:

    //сигнал окончания ввода символа для определенной кнопки MatrixWidget
    void EnteredSymbol(const std::string& symbol, size_t row, size_t colomn);

    //сигнал скролла ленты вверх или вниз
    void Scroll(std::string scroll_direction);
};


#endif //BLINDBROWSER_BUTTONS_H
