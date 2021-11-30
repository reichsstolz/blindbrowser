//
// Created by arty on 27.11.2021.
//

#ifndef BLINDBROWSER_DICTIONARY_HPP
#define BLINDBROWSER_DICTIONARY_HPP

#include <map>
#include <string>
#include <QIcon>
#include <QDir>

class Dictionary {
private:
    Dictionary();

    Dictionary(const Dictionary &) = delete;

    Dictionary &operator=(Dictionary &) = delete;

    //путь к директории с картинками
    QDir dictionary_path;

    //карта бинарное число->картинка
    std::map<const std::string, const QIcon *> dictionary_pictures_map;

public:
    static Dictionary &getDictionary();

    ~Dictionary();

    const QIcon *operator[](const std::string& binary_number);
};

#endif //BLINDBROWSER_DICTIONARY_HPP
