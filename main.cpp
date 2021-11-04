//
// Created by reichsstolz on 02.10.2021.
//
#include <Window.hpp>
#include <PyFunctions.hpp>

int main(int argc, char *argv[]) {
    std::vector<json> tags (make_json(post_req("https://yandex.ru/search/", "{\"text\": \"Van Darkholm\"}")));
    //std::cout<<post_req("https://yandex.ru/search/", "{\"text\": \"Van Darkholm\"}")<<std::endl;
    std::cout<< tags[3]["tag_type"]<<std::endl;
    QApplication app(argc, argv);
    Window MainWindow;
    MainWindow.show();
    return QApplication::exec();

    /*
      Post Requests


      Обычно в параметрах кнопок указаны методы передачи информации

      Например

      <button method="post"

      А на полях ввода указаны имена параметров, в которые нужно записать введённые данные

     */

}
