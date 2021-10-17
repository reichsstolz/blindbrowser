//
// Created by reichsstolz on 10.10.2021.
//

#include "PyFunctions.hpp"


void return_req(){
    py::scoped_interpreter guard{};

    py::module_ mainfile = py::module_::import("functions");
    string browser = mainfile.attr("make_request")("https://github.com").cast<string>();
    std::cout<<browser;
    //string req = browser.attr.cast<string>();

    //std::cout<<mainfile.attr("version").cast<string>();

    //py::module_ mainfile = py::module_::import("MainClasses");
    //auto  browser = mainfile.attr("Browser");
    //std::string req = browser.attr("_make_request")("https://github.com").cast<string>();
    //std::cout<<req;


    /*

     py::module_ mainfile = py::module_::import("MainClasses");
    auto  browser = mainfile.attr("Browser");
    std::string req = browser.attr("_make_request")("https://github.com").cast<string>();
    std::cout<<req;

     */
}
