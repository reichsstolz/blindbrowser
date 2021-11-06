//
// Created by reichsstolz on 02.10.2021.
//
#include <algorithm>
#include <QGridLayout>
#include <QLabel>
#include "MatrixWidget.hpp"
//#include "MatrixWidget.moc"
#include "moc_MatrixWidget.cpp"

MatrixWidget::MatrixWidget(QWidget *parent) : QFrame(parent) {
    setFrameStyle(QFrame::Box);
    auto *grid = new QGridLayout(this);

    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            //Создаем кнопочки, инициализируем их начальным текстом
            matrix_symbols[row][column] = new QPushButton( this);
            matrix_symbols[row][column]->setMinimumSize(15, 15);
            matrix_symbols[row][column]->setFont(QFont("Purisa", 10));

            //Нажатие на любую кнопку в режиме ввода генерирует сигнал, означающий необходимость ввода символа
            //Однако работает это только в режиме ввода
            connect(matrix_symbols[row][column], &QPushButton::clicked, this, [this, row, column]() {
                emit ClickedAnyButton(row, column);
            });

            grid->addWidget(matrix_symbols[row][column], row, column);
        }
    }

    //Строим страницу, изначально должна строиться страница базовая страница какого-то поисковика
    BuildPage(make_json(get_req("https://student.bmstu.ru/")));

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

void MatrixWidget::ChangeLocatorAndUpdate(const std::string &offset) {
    if (offset == "up" && locator != 0) {
        locator -= 20;
    }
    if ((offset == "down") && (locator + 20 != all_site_symbols.size())) {
        locator += 20;
    }
    UploadMatrix();
}

void MatrixWidget::BuildPage(const std::vector<json> &tags){
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
            matrix_symbols[row][column]->setText(QString::fromUtf8(all_site_symbols[row + locator][column]));
        }
    }
}

void MatrixWidget::OpenInputMode() {
    for (int row = 0; row < 20; ++row) {
        for (int column = 0; column < 10; ++column) {
            //если до этого в поле ввода что-то было, то оно должно разместиться здесь, например текущая ссылка
            matrix_symbols[row][column]->setText("");
        }
    }
    UnblockAllButtons();
}

void MatrixWidget::CloseInputMode() {
    BlockAllButtons();
    UploadMatrix();
}

void MatrixWidget::SetSymbol(size_t symbol, size_t row, size_t column) {
    matrix_symbols[row][column]->setText("Symbol");
    //особенность перехода на следующую кнопку при окончании ввода значения в предыдущую
    if (column == 9) {
        column = 0;
        ++row;
    } else {
        ++column;
    }
    if (!(column == 0 && row == 20)) {
        emit this->ClickedAnyButton(row, column);
    }
}

