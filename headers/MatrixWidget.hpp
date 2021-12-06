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
    std::string input_value; //строка, которую ввел пользователь, имеет вид "101011:101011:111111:..."
    size_t locator = 0; //указывает на ряд all_site_symbols, который должен показываться в matrix_symbols при чтении
public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

    //блокирует все кнопки
    void BlockAllButtons();

    //разблокирует все кнопки
    void UnblockAllButtons();

    //нормализует строку ввода, заполняя ее пробелами
    void NormalizeInputValue();

public
    slots:
    //обновляет показываемые матрицей значения в соответствии с текущим положение locator
    void ChangeLocatorAndUpdate(const std::string &offset);

    //строит страницу, получает ее домен в качестве параметра
    void BuildPage(const std::string &url);

    //обновляет кнопки символами, которые должны в них находится при текущей позиции locator
    void UploadMatrix();

    //запускает режим ввода текста, выводит уже введенное до этого значение
    void OpenInputMode(const std::string &previous_value);

    //возвращает введенную пользователем строку в ASCII
    std::string GetEntered();

    //закрываем режим ввода
    void CloseInputMode();

    //устанавливает символ в указанную ячейку после ввода с клавиатуры
    void SetSymbol(const std::string &symbol, size_t row, size_t colomn);

signals:

    //генерируется при нажатии на любую кнопку, либо при окончании ввода предыдущей символа для предыдущей кнопки
    void ClickedAnyButton(size_t row, size_t colomn);
};


#endif //BLINDBROWSER_MATRIXWIDGET_H
