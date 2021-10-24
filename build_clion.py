import py_compile, os


os.chdir("..")
print("Compiling python files...")
py_compile.compile("pyfiles/MainClasses.py", "cmake-build-debug/bin/MainClasses.pyc")
py_compile.compile("pyfiles/MinorClasses.py", "cmake-build-debug/bin/MinorClasses.pyc")
py_compile.compile("pyfiles/functions.py", "cmake-build-debug/bin/functions.pyc")
print("Compiling complete!")