import os, py_compile


os.chdir("..")
os.chdir("conan")
os.system("conan install .")
os.chdir("..")
py_compile.compile("python_files/MainClasses.py", "python_files/MainClasses.pyc")
py_compile.compile("python_files/MinorClasses.py", "python_files/MinorClasses.pyc")
py_compile.compile("python_files/functions.py", "python_files/functions.pyc")
os.system("cp python_files/MainClasses.pyc cmake-build-debug/bin")
os.system("cp python_files/functions.pyc cmake-build-debug/bin")
os.system("cp python_files/MinorClasses.pyc cmake-build-debug/bin")