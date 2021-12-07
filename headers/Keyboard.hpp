// Copyright 2021 Tinkerrer

#ifndef BLINDBROWSER_BUTTONS_H
#define BLINDBROWSER_BUTTONS_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <array>

class Keyboard : public QWidget {

private:
Q_OBJECT
    //массив указателей на основные рабочие кнопки
    std::array<QPushButton *, 6> keyboard_buttons{};
    //значение, введенное пользователем с клавиатуры
    std::string input_value;
public:
    explicit Keyboard(QWidget *parent = nullptr);

    ~Keyboard() override = default;

    //блокирует все рабочие кнопки
    void BlockAllButtons();

    //разблокирует все рабочие кнопки
    void UnblockAllButtons();

    //устанавливает функции основных рабочих кнопок и соответствующий им текст
    void ReturnButtonsFunctions();

public slots:

    //открывает режим ввода
    void OpenInputMode();

    //закрывает режим ввода
    void CloseInputMode();

    //функция ввода символа для определенной кнопки MatrixWidget
    void InputSymbol(size_t row, size_t column);

signals:

    //сигнал окончания ввода символа для определенной кнопки MatrixWidget
    void EnteredSymbol(const std::string &symbol, size_t row, size_t colomn);

    //сигнал скролла ленты вверх или вниз
    void Scroll(std::string scroll_direction);

    //сигнал о переходе к предыдущей или последующей странице
    void ForwardBackward(std::string go_direction);
};


#endif //BLINDBROWSER_BUTTONS_H
