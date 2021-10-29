//
// Created by arty on 16.10.2021.
//

#ifndef BLINDBROWSER_ADDRESSBAR_HPP
#define BLINDBROWSER_ADDRESSBAR_HPP

#include <QObject>
#include <QPushButton>
#include <array>
//#include "AddressBar.moc"

class AddressBar : public QPushButton {
Q_OBJECT
    std::array<std::array<QPushButton *, 10>, 20> matrix_symbols{};
public:
    explicit AddressBar(QWidget *parent = nullptr);

    ~AddressBar() override = default;

public slots:

signals:


};


#endif //BLINDBROWSER_ADDRESSBAR_HPP
