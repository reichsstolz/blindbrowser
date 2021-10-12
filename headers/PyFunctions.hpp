//
// Created by reichsstolz on 10.10.2021.
//

#ifndef BLINDBROWSER_PYFUNCTIONS_H
#define BLINDBROWSER_PYFUNCTIONS_H

//#include <pybind11/embed.h>
//#include <pybind11/pybind11.h>
//#include <pybind11/stl_bind.h>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <memory>
//#include <Python.h>



//namespace py = pybind11;
//using namespace py::literals;
using std::string;
using std::vector;
class Tag{
public:
    string tag_type;
    string data;
    vector<std::unique_ptr<Tag>> children;
    std::map<string, string> attrs;
    Tag(string  tag_type_, string  data_, vector<std::unique_ptr<Tag>> children_, std::map<string, string> attrs_ ): tag_type(std::move(tag_type_)), data(std::move(data_)), children(std::move(children_)), attrs(std::move(attrs_)){}
};

//string return_req(string url);

//int m();




#endif //BLINDBROWSER_PYFUNCTIONS_H
