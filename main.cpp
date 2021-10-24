//
// Created by reichsstolz on 02.10.2021.
//
#include <Window.hpp>
#include <PyFunctions.hpp>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window MainWindow;
    MainWindow.show();

<<<<<<< HEAD
    std::vector<json> tags (make_json(return_req("https://vk.com")));

      /*json example  for Artem
      make_json returns a vector with json objects
      you can use them just like list and dict in Python*/

    std::cout<< tags[0]["children"]<<std::endl;
    std::cout<< tags[0]["children"][0]<<std::endl;
    std::cout<< tags[0]["data"];
    return QApplication::exec();
=======
    /*
     * JSON TIME
     *
     * std::vector<json> tags (make_json(return_req("https://vk.com")));
     *
     * json example  for Artem
     * make_json returns a vector with json objects
     * you can use them just like list and dict in Python
     *
     * std::cout<< tags[0]["children"]<<std::endl;
     * std::cout<< tags[0]["childrstd::cout<< tags[0]["children"]<<std::endl;en"][0]<<std::endl;
     * std::cout<< tags[0]["data"];
     */
    std::vector<json> tags (make_json(return_req("https://vk.com")));
    std::cout<< tags[0]["children"]<<std::endl;
>>>>>>> 254ce79f2b348c1cf76ebcbb37891b002b60a72c
    //return 0;
}
