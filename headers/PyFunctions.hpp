//Copyright 2021 reichsstolz

#ifndef BLINDBROWSER_PYFUNCTIONS_H
#define BLINDBROWSER_PYFUNCTIONS_H


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <regex>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

#pragma push_macro("slots")
#undef slots
#include <pybind11/embed.h>
#pragma pop_macro("slots")

namespace py = pybind11;
using std::string;
using std::vector;


string get_req(const string& url);

string post_req(const string& url, const string& data);

vector<json> make_json(const string& req);

string trans_brail(const string& str);

string trans_ascii(const string& brail);



#endif //BLINDBROWSER_PYFUNCTIONS_H
