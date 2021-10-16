//
// Created by reichsstolz on 02.10.2021.
//


#include <QGridLayout>
#include <QLabel>
#include "MatrixWidget.hpp"
//#include "MatrixWidget.moc"
#include "moc_MatrixWidget.cpp"

MatrixWidget::MatrixWidget(QWidget *parent): QFrame(parent) {
    setFrameStyle(QFrame::Box);
    auto *grid = new QGridLayout(this);
    for(int row = 0; row < 20; ++row){
        for(int colomn = 0; colomn < 10; ++colomn){
            matrix_symbols[row][colomn] = new QLabel("A",this);
            matrix_symbols[row][colomn]->setMinimumSize(15, 15);
            matrix_symbols[row][colomn]->setFont(QFont("Purisa", 15));
            grid->addWidget(matrix_symbols[row][colomn], row, colomn);
        }
    }
    setMinimumSize(600, 600);
    grid->setSpacing(4);
    grid->setVerticalSpacing(4);

    setLayout(grid);
}

void MatrixWidget::OpenInputMode() {

}
