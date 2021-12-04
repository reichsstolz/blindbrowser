//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QPushButton>
#include <string>
//#include "AddressBar.moc"

class AddressBar : public QPushButton {
Q_OBJECT
    //ссылка текущей страницы
    std::string current_url;
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

public slots:

    //обработка введенного пользователем домена
    void ProcessURL(const std::string &entered_url);

    //возвращает текущий домен
    std::string GetCurrentURL();

signals:

    //сигнал, означающий, что обработка введенного домена закончена, необходимо построить страницу
    void OpenPage(std::string domain);

};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
