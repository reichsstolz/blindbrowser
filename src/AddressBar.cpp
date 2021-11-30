//
// Created by arty on 16.10.2021.
//

#include "AddressBar.hpp"
//#include "AddressBar.moc"
#include "moc_AddressBar.cpp"

AddressBar::AddressBar(QWidget *parent) : QPushButton(parent), current_url("https://yandex.ru") {
    setMinimumHeight(30);
    setFont(QFont("Purisa", 15));
}

void AddressBar::ProcessURL(const std::string &entered_url) {
    current_url = entered_url;
    emit OpenPage(current_url);
}

std::string AddressBar::GetCurrentURL() {
    return current_url;
}

