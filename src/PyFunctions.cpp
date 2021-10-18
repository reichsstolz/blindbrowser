//
// Created by reichsstolz on 10.10.2021.
//

#include "PyFunctions.hpp"
/*
 HOW TO USE JSON

*/
string return_req(const string& url){
    py::scoped_interpreter guard{};

    py::module_ mainfile = py::module_::import("functions");
    string req = mainfile.attr("make_request")(url).cast<string>();
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