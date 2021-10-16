//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QLineEdit>
//#include "AddressBar.moc"
//

class AddressBar : public QLineEdit {
Q_OBJECT
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

public slots:

signals:

    void EditAddress();
};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
