//
// Created by reichsstolz on 10.10.2021.
//

#include "PyFunctions.hpp"


string return_req(string url){
    string sum;

    setenv("PYTHONPATH", ".", 1);
    namespace python = boost::python;
    // Initialize Python.
    Py_Initialize();

    try
    {
        // >>> import MyPythonClass
        python::object my_python_class_module = python::import("MainClasses");

        // >>> dog = MyPythonClass.Dog()
        python::object browser = my_python_class_module.attr("Browser")();

        // >>> dog.bark("woof");
        browser.attr("_make_request")(url);
    }
    catch (const python::error_already_set&)
    {
        PyErr_Print();
    }

    return sum;
}


