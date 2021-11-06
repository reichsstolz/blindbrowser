//
// Created by reichsstolz on 02.10.2021.
//
#include <Window.hpp>
#include <PyFunctions.hpp>

int main(int argc, char *argv[]) {
    std::vector<json> tags(make_json(get_req("https://student.bmstu.ru/")));
    for (auto &tag: tags) {
        if (!tag["data"].empty() && tag["tag_type"] != "script" && tag["tag_type"] != "style") {
            std::cout << tag << std::endl;
        }
    }
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
