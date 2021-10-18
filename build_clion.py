import os, py_compile


os.chdir("..")
os.chdir("conan")
os.system("conan install .")
os.chdir("..")
py_compile.compile("python_files/MainClasses.py", "cmake-build-debug/bin/MainClasses.pyc")
py_compile.compile("python_files/MinorClasses.py", "cmake-build-debug/bin/MinorClasses.pyc")
py_compile.compile("python_files/functions.py", "cmake-build-debug/bin/functions.pyc")
