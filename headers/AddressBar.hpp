//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QPushButton>
//#include "AddressBar.moc"

class AddressBar : public QPushButton {
Q_OBJECT
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

public slots:

signals:


};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
