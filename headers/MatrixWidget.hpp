// Copyright 2021 Tinkerrer

#ifndef BLINDBROWSER_MATRIXWIDGET_H
#define BLINDBROWSER_MATRIXWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <array>

#include <PyFunctions.hpp>

class MatrixWidget : public QFrame {
Q_OBJECT
    //массив отображаемых символов в режиме вывода
    std::array<std::array<QPushButton *, 10>, 20> matrix_symbols{};
    //вектор ВСЕХ символов странички, получаемый при переходе по ссылке
    std::vector<std::array<std::string, 10>> all_site_symbols;
    //строка, которую ввел пользователь, имеет вид "101011:101011:111111:..."
    std::string input_value;
    //указывает на ряд all_site_symbols, который должен показываться в matrix_symbols при чтении
    size_t locator = 0;

public:
    explicit MatrixWidget(QWidget *parent = nullptr);

    ~MatrixWidget() override = default;

    //блокирует все кнопки
    void BlockAllButtons();

    //разблокирует все кнопки
    void UnblockAllButtons();

    //нормализует строку ввода, заполняя ее пробелами
    void NormalizeInputValue();

    //возвращает введенную пользователем строку в ASCII
    std::string GetEntered();

public
    slots:
    //меняет положение locator в зависимости от параметрасам
    //обновляет показываемые матрицей иконки в соответствии с текущим положение locator
    void ChangeLocatorAndUpdate(const std::string &offset);

    //строит страницу, получает ее url в качестве параметра
    void BuildPage(const std::string &url);

    //обновляет кнопки, ставя в них иконки, которые должны в них находится при текущей позиции locator
    void UploadMatrix();

    //запускает режим ввода текста, выводит на дисплей параметр - значение, введенное пользователем до этого
    void OpenInputMode(const std::string &previous_value);

    //закрывает режим ввода
    void CloseInputMode();

    //устанавливает иконку в указанную ячейку, в качестве параметров получает введенный символ, строку и столбец кнопки
    void SetSymbol(const std::string &symbol, size_t row, size_t colomn);

signals:

    //генерируется при нажатии на любую кнопку, либо при окончании ввода предыдущего символа,
    //передает в качестве параметров строку и столбец кнопки
    void ClickedAnyButton(size_t row, size_t colomn);
};


#endif //BLINDBROWSER_MATRIXWIDGET_H
