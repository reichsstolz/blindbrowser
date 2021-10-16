//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H


#include <QObject>
#include <QFrame>
#include <QLabel>
#include <array>

// Виджет экранчика в центре "телефона"
// Он представляет из себя матрицу 10 на 20 в каждую ячейку, которой мы вписываем один символ
// https://ravesli.com/urok-12-risovanie-v-qt5/
// https://ravesli.com/urok-13-sozdanie-polzovatelskogo-vidzheta-v-qt5/

class MatrixWidget : public QFrame {
    Q_OBJECT
    std::array<std::array<QLabel *, 10>, 20> matrix_symbols;

public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

public slots:

    void OpenInputMode();

signals:

};


#endif //BLINDBROWSER_MATRIXWIDGET_H
