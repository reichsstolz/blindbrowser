//
// Created by reichsstolz on 10.10.2021.
//

#include "PyFunctions.hpp"
/*
 HOW TO USE POST REQ


     Найди инпут и его и имя передай вместе с именем то, что ввёл пользователь
     ---------------
     |    User     |  <input name="username" ...
     ---------------
     |  Password   |  <input name="password" ...
     ---------------
       [ submit ]

       JSON
    {
      "username":"User"
      "password":"Password"
    }

*/
string get_req(const string& url){
    py::scoped_interpreter guard{};

    py::module_ mainfile = py::module_::import("functions");
    string req = mainfile.attr("get_request")(url).cast<string>();
    return req;

}
string post_req(const string& url, const string& data){
  py::scoped_interpreter guard{};

  py::module_ mainfile = py::module_::import("functions");
  string req = mainfile.attr("post_request")(url, data).cast<string>();
  return req;
}

vector<json> make_json(const string& req) {
    vector<json> tags;
    json tag;
    size_t count = 0;
    size_t last_parsed = 0;
    for (auto i = 0; i < req.size(); ++i) {
        if (req[i] == 125) {
            count += 1;
        }
        if (count == 2) {
            count = 0;
            tag = json::parse(req.begin() + last_parsed, req.begin() + i+1);
            last_parsed = i+1;
            tags.emplace_back(tag);
        }
    }
    return tags;
}
