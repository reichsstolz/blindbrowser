// Copyright 2021 Tinkerrer

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QPushButton>
#include <string>
#include <vector>
#include <iterator>

//ссылочная кнопка, отвечает за переход по ссылкам, хранит историю бразуера
class AddressBar : public QPushButton {
Q_OBJECT
    //вектор всех ссылок страниц (история браузера), хранится в ASCII
    std::vector<std::string> url_history{"https://yandex.ru/"};
    //итератор, указывающий на текущую страницу
    std::vector<std::string>::const_iterator current_url;
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

    //возвращает текущий домен
    std::string GetCurrentURL();

public slots:

    //обработка введенной пользователем ссылки, запускает открытие страницы
    void ProcessURL(const std::string &entered_url);

    //переходит на страницу вперед/назад, если это возможно
    void GoToForwardBackwardPage(const std::string &direction);

signals:

    //означает, что обработка введенной url закончена, необходимо построить страницу
    void OpenPage(std::string domain);

};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
