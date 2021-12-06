//
// Created by arty on 16.10.2021.
//

#include "AddressBar.hpp"
//#include "AddressBar.moc"
#include "moc_AddressBar.cpp"

AddressBar::AddressBar(QWidget *parent) : QPushButton(parent), current_url(url_history.begin()) {
    setMinimumHeight(30);
    setFont(QFont("Purisa", 15));
}

void AddressBar::ProcessURL(const std::string &entered_url) {
    if (current_url != url_history.cend() - 1) {
        url_history.erase(current_url + 1, url_history.cend());
    }
    url_history.push_back(entered_url);
    current_url = url_history.end();
    --current_url;
    emit OpenPage(entered_url);
}

std::string AddressBar::GetCurrentURL() {
    return *current_url;
}

void AddressBar::GoToForwardBackwardPage(const std::string &direction) {
    if (direction == "forward" && current_url != url_history.cend() - 1) {
        ++current_url;
        emit OpenPage(*current_url);
    }
    if (direction == "backward" && current_url != url_history.cbegin()) {
        --current_url;
        emit OpenPage(*current_url);
    }
}

