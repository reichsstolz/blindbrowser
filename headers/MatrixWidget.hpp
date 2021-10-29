//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H


#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <array>
//#include "MatrixWidget.moc"
//#include "moc_MatrixWidget.cpp"

class MatrixWidget : public QFrame {
Q_OBJECT
    std::array<std::array<QPushButton *, 10>, 20> matrix_symbols{}; //массив отображаемых символов в режиме вывода
public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

    //блокирует все кнопки
    void BlockAllButtons();
    //разблокирует все кнопки
    void UnblockAllButtons();
public slots:
    //получает на вход дерево, обрабатывает его и строит страничку для чтения
    void BuildPage();
    //запускает режим ввода текста
    void OpenInputMode();
    //закрываем режим ввода
    void CloseInputMode();
    //устанавливает символ в указанную ячейку после ввода с клавиатуры
    void SetSymbol(size_t symbol, size_t row, size_t colomn);

signals:
    //генерируется при нажатии на любую кнопку, либо при окончании ввода предыдущей символа для предыдущей кнопки
    void ClickedAnyButton(size_t row, size_t colomn);
};


#endif //BLINDBROWSER_MATRIXWIDGET_H
