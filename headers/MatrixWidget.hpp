//
// Created by reichsstolz on 02.10.2021.
//

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H


#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <array>

#include <PyFunctions.hpp>
//#include "MatrixWidget.moc"
//#include "moc_MatrixWidget.cpp"

class MatrixWidget : public QFrame {
Q_OBJECT
    std::array<std::array<QPushButton *, 10>, 20> matrix_symbols{}; //массив отображаемых символов в режиме вывода
    std::vector<std::array<std::string, 10>> all_site_symbols; //вектор ВСЕХ символов странички, получаемый при переходе по ссылке
    size_t locator = 0; //указывает на ряд all_site_symbols, который должен показываться в matrix_symbols
public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

    //блокирует все кнопки
    void BlockAllButtons();

    //разблокирует все кнопки
    void UnblockAllButtons();

public slots:
    //обновляет показываемые матрицей значения в соответствии с текущим положение locator
    void ChangeLocatorAndUpdate(const std::string &offset);

    //строит страницу после запроса
    void BuildPage(const std::vector<json> &tags);

    //обновляет кнопки символами, которые должны в них находится при текущей позиции locator
    void UploadMatrix();

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
