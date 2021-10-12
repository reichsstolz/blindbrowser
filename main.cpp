//
// Created by reichsstolz on 02.10.2021.
//
#include <Window.hpp>
//#include <PyFunctions.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window MainWindow;
    MainWindow.show();
    return QApplication::exec();
    //m();
    return 0;
}
