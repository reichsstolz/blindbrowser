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

MatrixWidget::MatrixWidget(QWidget *parent) : QFrame(parent) {
    setFrameStyle(QFrame::Box);
    auto *grid = new QGridLayout(this);

    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            //Создаем кнопочки, задаем их размер
            matrix_symbols[row][column] = new QPushButton(this);
            matrix_symbols[row][column]->setMinimumSize(15, 15);

            //Нажатие на любую кнопку в режиме ввода генерирует сигнал, означающий необходимость ввода символа
            //Однако работает это только в режиме ввода
            connect(matrix_symbols[row][column], &QPushButton::clicked, this, [this, row, column]() {
                emit ClickedAnyButton(row, column);
            });

            grid->addWidget(matrix_symbols[row][column], row, column);
        }
    }

    //Строим страницу, изначально должна строиться страница базовая страница какого-то поисковика,
    //то есть функция получает в качестве параметра URL базовой страницы
    BuildPage("https://yandex.ru/");
    //Изначально в режиме чтения все кнопки заблокированы
    BlockAllButtons();

    setMinimumSize(600, 600);
    grid->setSpacing(4);
    grid->setVerticalSpacing(4);
    setLayout(grid);
}

void MatrixWidget::BlockAllButtons() {
    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->blockSignals(true);
        }
    }
}

void MatrixWidget::UnblockAllButtons() {
    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->blockSignals(false);
        }
    }
}

void MatrixWidget::NormalizeInputValue() {
    while (input_value.size() <= 7 * 200) {
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

    json tags(make_json(get_req(url)));
    //обрабатываем дерево тегов
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

    //конвертация в Брайль
    all_page_data = trans_brail(all_page_data);

    //генерируем целое число блоков 20x10 символов страницы
    //200-количество ячеек в блоке, 7 - длина последовательности 1 символа в Брайле
    all_site_symbols.resize(
            (all_page_data.size() / (200 * 7) + ((all_page_data.size() / 7 % 200) ? 1 : 0)) * 20);
    //возрщащаем ползунок в начальное положение
    locator = 0;

    //заполняем вектор всех символов страницы
    size_t row = 0;
    size_t column = 0;
    while (!all_page_data.empty()) {
        all_site_symbols[row][column] = all_page_data.substr(0, 7);
        all_page_data.erase(0, 7);
        column = (column + 1) % 10;
        if (!column) {
            ++row;
        }
    }

    //дозаполним оставшиеся пустые символы пробелами
    while (row % 20) {
        all_site_symbols[row][column] = "000000:";
        column = (column + 1) % 10;
        if (!column) {
            ++row;
        }
    }

    //заполняем кнопки отображаемыми символами при текущей позиции locator
    UploadMatrix();
}

void MatrixWidget::UploadMatrix() {
    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->setIcon(
                    *(Dictionary::getDictionary()[all_site_symbols[row + locator][column]]));
        }
    }
}

void MatrixWidget::OpenInputMode(const std::string &previous_value) {
    input_value = trans_brail(previous_value);
    //нормализует вводимое пользователем значение, по умолчанию ставятся все пробелы, то есть "000000:000000:000000:..."
    NormalizeInputValue();
    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->setIcon(
                    *(Dictionary::getDictionary()[input_value.substr(7 * (column + 10 * row), 7)]));
        }
    }
    UnblockAllButtons();
}

std::string MatrixWidget::GetEntered() {
    return trans_ascii(input_value);
}

void MatrixWidget::CloseInputMode() {
    for (size_t row = 0; row < 20; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            matrix_symbols[row][column]->setIcon(QIcon());
        }
    }
    BlockAllButtons();
    UploadMatrix();
}

void MatrixWidget::SetSymbol(const std::string &symbol, size_t row, size_t column) {
    matrix_symbols[row][column]->setIcon(*(Dictionary::getDictionary()[symbol]));
    for (size_t i = 0; i < 6; ++i) {
        input_value[i + 7 * column + 7 * 10 * row] = symbol[i];
    }
    //особенность перехода на следующую кнопку при окончании ввода значения в предыдущую
    ++column;
    column %= 10;
    if (column == 0) {
        ++row;
        row %= 20;
    }
    emit this->ClickedAnyButton(row, column);
}

