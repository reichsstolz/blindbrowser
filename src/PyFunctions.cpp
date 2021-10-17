//
// Created by reichsstolz on 10.10.2021.
//

#include "PyFunctions.hpp"


string return_req(const string& url){
    py::scoped_interpreter guard{};

    py::module_ mainfile = py::module_::import("functions");
    string req = mainfile.attr("make_request")(url).cast<string>();
    return req;

}

