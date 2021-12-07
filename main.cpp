// Copyright 2021 reichsstolz & Tinkerrer

#include <Window.hpp>

int main(int argc, char *argv[]) {
    //запуск приложения
    QApplication app(argc, argv);
    //создание главного окна приложения
    Window MainWindow;
    //показать главное окно
    MainWindow.show();
    return QApplication::exec();
}
