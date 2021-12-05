//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QPushButton>
#include <string>
#include <vector>
#include <iterator>
//#include "AddressBar.moc"

class AddressBar : public QPushButton {
Q_OBJECT
    //история всех ссылок страниц, хранится в ASCII
    std::vector<std::string> url_history{"https://yandex.ru/"};
    //итератор, указывающий на текущую страницу
    std::vector<std::string>::const_iterator current_url;
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

public slots:

    //обработка введенного пользователем домена
    void ProcessURL(const std::string &entered_url);

    //возвращает текущий домен
    std::string GetCurrentURL();

    //переходит на страницу вперед/назад
    void GoToForwardBackwardPage(const std::string &direction);

signals:

    //сигнал, означающий, что обработка введенного домена закончена, необходимо построить страницу
    void OpenPage(std::string domain);

};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
