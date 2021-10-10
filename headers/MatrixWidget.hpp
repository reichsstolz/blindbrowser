//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H


#include <QWidget>
#include <QFrame>
// Виджет экранчика в центре "телефона"
// Он представляет из себя матрицу 10 на 20 в каждую ячейку, которой мы вписываем один символ
// https://ravesli.com/urok-12-risovanie-v-qt5/
// https://ravesli.com/urok-13-sozdanie-polzovatelskogo-vidzheta-v-qt5/

class MatrixWidget : public QFrame {
private:
    //QOBJECT
public:
    explicit MatrixWidget(QWidget *parent = nullptr);

};


#endif //BLINDBROWSER_MATRIXWIDGET_H
