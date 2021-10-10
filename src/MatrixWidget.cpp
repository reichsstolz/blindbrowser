//
// Created by reichsstolz on 02.10.2021.
//

#include "MatrixWidget.hpp"
#include <QGridLayout>
#include <QLabel>
#include <array>

MatrixWidget::MatrixWidget(QWidget *parent): QFrame(parent) {
    std::array<std::array<QLabel*, 10>, 20> matrix_array;
    setFrameStyle(QFrame::Box);
    QGridLayout *grid = new QGridLayout(this);
    for(int row = 0; row < 20; ++row){
        for(int colomn = 0; colomn < 10; ++colomn){
            matrix_array[row][colomn] = new QLabel("A",this);
            matrix_array[row][colomn]->setMinimumSize(15, 15);
            matrix_array[row][colomn]->setFont(QFont("Purisa", 15));
            grid->addWidget(matrix_array[row][colomn], row, colomn);
        }
    }
    setMinimumSize(600, 600);
    grid->setSpacing(4);
    grid->setVerticalSpacing(4);

    setLayout(grid);
}