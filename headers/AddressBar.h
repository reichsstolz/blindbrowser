//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_H
#define BLINDBROWSER_ADDRESSBAR_H

#include <QLineEdit>

class AddressBar : public QLineEdit {
    Q_OBJECT

public:
    explicit AddressBar(QWidget *parent = nullptr);

    virtual ~AddressBar() override = default;

public slots:

signals:

    void EditAdress();
};


#endif //BLINDBROWSER_ADDRESSBAR_H
