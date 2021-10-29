//
// Created by reichsstolz on 02.10.2021.
//

#include <QGridLayout>
#include <QLabel>
#include "MatrixWidget.hpp"
//#include "MatrixWidget.moc"
#include "moc_MatrixWidget.cpp"

MatrixWidget::MatrixWidget(QWidget *parent) : QFrame(parent) {
    setFrameStyle(QFrame::Box);
    auto *grid = new QGridLayout(this);

    for (int row = 0; row < 20; ++row) {
        for (int colomn = 0; colomn < 10; ++colomn) {
            //Создаем кнопочки
            matrix_symbols[row][colomn] = new QPushButton("A", this);
            matrix_symbols[row][colomn]->setMinimumSize(15, 15);
            matrix_symbols[row][colomn]->setFont(QFont("Purisa", 15));

            //Нажатие на любую кнопку в режиме ввода генерирует сигнал, означающий необходимость ввода символа
            connect(matrix_symbols[row][colomn], &QPushButton::clicked, this, [=]() {
                emit ClickedAnyButton(row, colomn);
            });

            grid->addWidget(matrix_symbols[row][colomn], row, colomn);
        }
    }

    //Изначально в режиме чтения все кнопки заблокированы
    BlockAllButtons();

    setMinimumSize(600, 600);
    grid->setSpacing(4);
    grid->setVerticalSpacing(4);
    setLayout(grid);
}

void MatrixWidget::BlockAllButtons() {
    for (int row = 0; row < 20; ++row) {
        for (int colomn = 0; colomn < 10; ++colomn) {
            matrix_symbols[row][colomn]->blockSignals(true);
        }
    }
}

void MatrixWidget::UnblockAllButtons() {
    for (int row = 0; row < 20; ++row) {
        for (int colomn = 0; colomn < 10; ++colomn) {
            matrix_symbols[row][colomn]->blockSignals(false);
        }
    }
}

void MatrixWidget::BuildPage() {

}

void MatrixWidget::OpenInputMode() {
    for (int row = 0; row < 20; ++row) {
        for (int colomn = 0; colomn < 10; ++colomn) {
            //если до этого в поле ввода что-то было, то оно должно разместиться здесь
            matrix_symbols[row][colomn]->setText("");
        }
    }
    UnblockAllButtons();
}

void MatrixWidget::CloseInputMode() {
    for (int row = 0; row < 20; ++row) {
        for (int colomn = 0; colomn < 10; ++colomn) {
            //если до этого в поле ввода что-то было, то оно должно разместиться здесь
            matrix_symbols[row][colomn]->setText("A");
        }
    }
    BlockAllButtons();
}

void MatrixWidget::SetSymbol(size_t symbol, size_t row, size_t colomn) {
    matrix_symbols[row][colomn]->setText("Symbol");
    //особенность перехода на следующую кнопку при окончании ввода значения в предыдущую
    if (colomn == 9) {
        colomn = 0;
        ++row;
    }
    else{
        ++colomn;
    }
    if(!(colomn == 0 && row == 20)){
        emit this->ClickedAnyButton(row, colomn);
    }
}

