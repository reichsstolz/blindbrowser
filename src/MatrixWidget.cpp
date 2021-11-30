//
// Created by reichsstolz on 02.10.2021.
//
#include <algorithm>
#include <QGridLayout>
#include <QLabel>
#include "MatrixWidget.hpp"
#include <Dictionary.hpp>
//#include "MatrixWidget.moc"
#include <QStyle>
#include "moc_MatrixWidget.cpp"

MatrixWidget::MatrixWidget(QWidget *parent) : QFrame(parent){
    setFrameStyle(QFrame::Box);
    auto *grid = new QGridLayout(this);

    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            //Создаем кнопочки, задаем их размер
            matrix_symbols[row][column] = new QPushButton(this);
            matrix_symbols[row][column]->setMinimumSize(15, 15);
            //matrix_symbols[row][column]->setFont(QFont("Purisa", 10));

            //Нажатие на любую кнопку в режиме ввода генерирует сигнал, означающий необходимость ввода символа
            //Однако работает это только в режиме ввода
            connect(matrix_symbols[row][column], &QPushButton::clicked, this, [this, row, column]() {
                emit ClickedAnyButton(row, column);
            });

            grid->addWidget(matrix_symbols[row][column], row, column);
        }
    }

    //Строим страницу, изначально должна строиться страница базовая страница какого-то поисковика,
    //то есть функция получает в качестве параметра домен базовой страницы
    BuildPage(
            "https://www.google.com/search?q=Gayparty&client=ms-android-xiaomi-rev1&ei=XfukYbKUJ4bbrgTg9ra4Dw&oq=Gayparty&gs_lcp=ChNtb2JpbGUtZ3dzLXdpei1zZXJwEAM6BAgAEEc6CggAELEDEIMBEEM6CAgAEIAEELEDOgUIABCABDoECAAQQzoNCC4QsQMQxwEQ0QMQQzoHCAAQsQMQQzoKCC4QxwEQowIQQzoECC4QQzoLCAAQgAQQsQMQgwE6CAgAELEDEIMBOggILhCABBCxAzoICC4QsQMQgwE6BggAEAoQQzoHCAAQgAQQCjoJCAAQChBGEP8BOgQIABAKUIoQWPNLYKFQaABwAXgBgAHNAYgB-AySAQUwLjkuMZgBAKABAbABAMgBCMABAQ&sclient=mobile-gws-wiz-serp");

    //Изначально в режиме чтения все кнопки заблокированы
    BlockAllButtons();

    setMinimumSize(600, 600);
    grid->setSpacing(4);
    grid->setVerticalSpacing(4);
    setLayout(grid);
}

void MatrixWidget::BlockAllButtons() {
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->blockSignals(true);
        }
    }
}

void MatrixWidget::UnblockAllButtons() {
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->blockSignals(false);
        }
    }
}

void MatrixWidget::NormalizeInputValue() {
    while(input_value.size() != 7 * 200){
        input_value.append("000000:");
    }
}

void MatrixWidget::ChangeLocatorAndUpdate(const std::string &offset) {
    if (offset == "up" && locator != 0) {
        locator -= 20;
    }
    if ((offset == "down") && (locator + 20 != all_site_symbols.size())) {
        locator += 20;
    }
    UploadMatrix();
}

void MatrixWidget::BuildPage(const std::string &url) {

    //ТУТ, при необходимости, ДОЛЖНА БЫТЬ КОНВЕРТАЦИЯ ИЗ БРАЙЛЯ url

    json tags(make_json(get_req(url)));
    //обрабатываем дерево
    std::string all_page_data;
    for (auto &tag: tags) {
        if (!tag["data"].empty() && (tag["tag_type"] != "script") && (tag["tag_type"] != "style") &&
            (tag["tag_type"] != "noframes")) {
            all_page_data += tag["data"];
            for (size_t i = all_page_data.size() % 10; i % 10 != 0; ++i) {
                all_page_data += ' ';
            }
        }
    }

    //ТУТ ДОЛЖНА БЫТЬ КОНВЕРТАЦИЯ В БРАЙЛЬ all_page_data

    //генерируем целое число блоков 20x10
    all_site_symbols.resize((all_page_data.size() / 200 + 1) * 200);
    locator = 0;

    //заполняем вектор всех символов страницы
    for (size_t row = 0; row < all_page_data.size(); ++row) {
        for (size_t column = 0; column < 10; ++column) {
            all_site_symbols[row][column] = all_page_data[10 * row + column];
        }
    }

    //заполняем кнопки отображаемыми символами при текущей позиции locator
    UploadMatrix();
}

void MatrixWidget::UploadMatrix() {
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->setIcon(
                    *(Dictionary::getDictionary()[all_site_symbols[row + locator][column]]));
        }
    }
}

void MatrixWidget::OpenInputMode(const std::string &previous_value) {
    //нормализует вводимое пользователем значение, по умолчанию ставятся все пробелы, то есть "000000:000000:000000:..."
    NormalizeInputValue();
    input_value = previous_value;
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            //поставить иконки с пустым текстом на Брайле
            matrix_symbols[row][column]->setIcon(QIcon());
        }
    }
    UnblockAllButtons();
}

std::string MatrixWidget::GetEntered() {
    return input_value;
}

void MatrixWidget::CloseInputMode() {
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->setIcon(QIcon());
        }
    }
    BlockAllButtons();
    UploadMatrix();
}

void MatrixWidget::SetSymbol(const std::string &symbol, size_t row, size_t column) {
    matrix_symbols[row][column]->setIcon(*(Dictionary::getDictionary()[symbol]));
    for(size_t i = 0; i < 6; ++i){
        input_value[i + 7 * (row + 1) * column] = symbol[i];
    }
    //matrix_symbols[row][column]->setIconSize(QSize(65, 65));
    //особенность перехода на следующую кнопку при окончании ввода значения в предыдущую
    ++column;
    column %= 10;
    if (column == 0) {
        ++row;
        row %= 20;
    }
    emit this->ClickedAnyButton(row, column);
}

