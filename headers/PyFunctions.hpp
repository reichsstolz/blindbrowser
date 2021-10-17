//
// Created by reichsstolz on 10.10.2021.
//

#ifndef BLINDBROWSER_PYFUNCTIONS_H
#define BLINDBROWSER_PYFUNCTIONS_H


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>
/*#pragma push_macro("slots")
#undef slots
#include <boost/python.hpp>
#pragma pop_macro("slots")*/
#include <pybind11/embed.h>
namespace py = pybind11;
using std::string;
using std::vector;

class Tag{
public:
    string tag_type;
    string data;
    vector<string> children;
    std::map<string, string> attrs;
    Tag(const string& json);
};

string return_req(const string& url);






#endif //BLINDBROWSER_PYFUNCTIONS_H
