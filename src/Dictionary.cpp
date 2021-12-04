//
// Created by arty on 27.11.2021.
//

#include <Dictionary.hpp>
#include <iostream>

Dictionary::Dictionary() : dictionary_path(QDir::current()) {
    //добираемся до директории с картинками
    dictionary_path.cdUp();
    dictionary_path.cdUp();
    dictionary_path.cd(dictionary_path.path() + "/pics/Braille.ico");
    dictionary_pictures_map.insert({
        //буквы и цифры
        {"100000:", new QIcon(dictionary_path.path() + "/A1.ico")},
        {"110000:", new QIcon(dictionary_path.path() + "/B2.ico")},
        {"100100:", new QIcon(dictionary_path.path() + "/C3.ico")},
        {"100110:", new QIcon(dictionary_path.path() + "/D4.ico")},
        {"100010:", new QIcon(dictionary_path.path() + "/E5.ico")},
        {"110100:", new QIcon(dictionary_path.path() + "/F6.ico")},
        {"110110:", new QIcon(dictionary_path.path() + "/G7.ico")},
        {"110010:", new QIcon(dictionary_path.path() + "/H8.ico")},
        {"010100:", new QIcon(dictionary_path.path() + "/I9.ico")},
        {"010110:", new QIcon(dictionary_path.path() + "/J0.ico")},
        {"101000:", new QIcon(dictionary_path.path() + "/K.ico")},
        {"111000:", new QIcon(dictionary_path.path() + "/L.ico")},
        {"101100:", new QIcon(dictionary_path.path() + "/M.ico")},
        {"101110:", new QIcon(dictionary_path.path() + "/N.ico")},
        {"101010:", new QIcon(dictionary_path.path() + "/O.ico")},
        {"111100:", new QIcon(dictionary_path.path() + "/P.ico")},
        {"111110:", new QIcon(dictionary_path.path() + "/Q.ico")},
        {"111010:", new QIcon(dictionary_path.path() + "/R.ico")},
        {"011100:", new QIcon(dictionary_path.path() + "/S.ico")},
        {"011110:", new QIcon(dictionary_path.path() + "/T.ico")},
        {"101001:", new QIcon(dictionary_path.path() + "/U.ico")},
        {"111001:", new QIcon(dictionary_path.path() + "/V.ico")},
        {"010111:", new QIcon(dictionary_path.path() + "/W.ico")},
        {"101101:", new QIcon(dictionary_path.path() + "/X.ico")},
        {"101111:", new QIcon(dictionary_path.path() + "/Y.ico")},
        {"101011:", new QIcon(dictionary_path.path() + "/Z.ico")},
        //знаки препинания
        {"000000:", new QIcon(QIcon())}, //пробел
        {"011011:", new QIcon(dictionary_path.path() + "/At.ico")},
        {"010010:", new QIcon(dictionary_path.path() + "/Colon.ico")},
        {"010000:", new QIcon(dictionary_path.path() + "/Comma.ico")},
        {"000011:", new QIcon(dictionary_path.path() + "/Equality.ico")},
        {"011010:", new QIcon(dictionary_path.path() + "/ExclamationPoint.ico")},
        {"001001:", new QIcon(dictionary_path.path() + "/Slash.ico")},
        {"110001:", new QIcon(dictionary_path.path() + "/ParanthesisOpen.ico")},
        {"001110:", new QIcon(dictionary_path.path() + "/Plus.ico")},
        {"010011:", new QIcon(dictionary_path.path() + "/Point.ico")},
        {"010001:", new QIcon(dictionary_path.path() + "/QuestionMark.ico")},
        {"001011:", new QIcon(dictionary_path.path() + "/QuoteClose.ico")},
        {"011001:", new QIcon(dictionary_path.path() + "/QuoteOpen.ico")},
        {"011000:", new QIcon(dictionary_path.path() + "/Semicolon.ico")},
        //служебные символы
        {"000001:", new QIcon(dictionary_path.path() + "/CapitalSign.ico")},
        {"001111:", new QIcon(dictionary_path.path() + "/NumberSign.ico")},
    });
}

Dictionary::~Dictionary() {
    for (const auto dictionary_element: dictionary_pictures_map) {
        delete dictionary_element.second;
    }
}

Dictionary &Dictionary::getDictionary() {
    static Dictionary dictionary;
    return dictionary;
}

const QIcon *Dictionary::operator[](const std::string& binary_number) {
    return dictionary_pictures_map[binary_number];
}
