//
// Created by reichsstolz on 02.10.2021.
//
#include <Window.hpp>
#include <PyFunctions.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window MainWindow;
    MainWindow.show();

    std::vector<json> tags (make_json(return_req("https://vk.com")));

      /*json example  for Artem
      make_json returns a vector with json objects
      you can use them just like list and dict in Python*/

    std::cout<< tags[0]["children"]<<std::endl;
    std::cout<< tags[0]["children"][0]<<std::endl;
    std::cout<< tags[0]["data"];
    return QApplication::exec();
    //return 0;
}
