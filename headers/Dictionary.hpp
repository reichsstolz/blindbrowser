// Copyright 2021 Tinkerrer

#ifndef BLINDBROWSER_DICTIONARY_HPP
#define BLINDBROWSER_DICTIONARY_HPP

#include <map>
#include <string>
#include <QIcon>

//синглтон словарь, отображение: символ->иконка картинки
class Dictionary {
private:
    Dictionary();

    Dictionary(const Dictionary &) = delete;

    Dictionary &operator=(Dictionary &) = delete;

    //карта бинарное число->картинка
    std::map<const std::string, const QIcon *> dictionary_pictures_map;

public:
    //возвращает ссылку на синглтон словарь
    static Dictionary &getDictionary();

    ~Dictionary();

    //возврщает иконку, соответствующую переданному параметру, в случае,
    //если нужной иконки нет, возвращает пустую иконку
    const QIcon *operator[](const std::string &binary_number);
};

#endif //BLINDBROWSER_DICTIONARY_HPP
