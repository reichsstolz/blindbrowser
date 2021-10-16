//
// Created by arty on 16.10.2021.
//

#include "AddressBar.hpp"
//#include "AddressBar.moc"
#include "moc_AddressBar.cpp"

AddressBar::AddressBar(QWidget *parent) : QLineEdit(parent) {
    setMinimumHeight(30);
    setFont(QFont("Purisa", 15));
}

void AddressBar::EditAddress() {

}

