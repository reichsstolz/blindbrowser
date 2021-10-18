cmake_minimum_required(VERSION 3.3)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CONAN_DISABLE_CHECK_COMPILER ON)

include(conan/conan_paths.cmake)
include(conan/conanbuildinfo.cmake)


include_directories(${CONAN_INCLUDE_DIRS})

project(BlindBrowser)

conan_basic_setup()


find_package(Qt6  COMPONENTS Widgets Core)


add_library(${PROJECT_NAME} STATIC
        ./src/MatrixWidget.cpp
        ./src/Keyboard.cpp
        ./src/Window.cpp
        ./src/PyFunctions.cpp
        ./src/AddressBar.cpp
        )

add_executable(demo main.cpp)
add_dependencies(demo pyfiles)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>"
        "$<INSTALL_INTERFACE:headers>"
        )

target_link_libraries(demo ${PROJECT_NAME} ${CONAN_LIBS})


