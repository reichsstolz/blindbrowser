//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H


#include <QObject>
#include <QFrame>
#include <QLabel>
#include <array>
//#include "MatrixWidget.moc"
//#include "moc_MatrixWidget.cpp"

class MatrixWidget : public QFrame {
Q_OBJECT
    std::array<std::array<QLabel *, 10>, 20> matrix_symbols{}; //массив

public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

public slots:
    void BuildPage(); //получает на вход дерево, обрабатывает его и строит страничку
    void OpenInputMode(); //запускает режим ввода текста

signals:

};


#endif //BLINDBROWSER_MATRIXWIDGET_H
