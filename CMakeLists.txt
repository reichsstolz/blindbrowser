cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
        SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

project(BlindBrowser)

hunter_add_package(Qt)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)

add_library(${PROJECT_NAME} STATIC
        ./src/MatrixWidget.cpp
        ./src/Keyboard.cpp
        ./src/Window.cpp
        )
add_executable(demo main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/headers>"
        "$<INSTALL_INTERFACE:headers>"
        )

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
target_link_libraries(demo ${PROJECT_NAME})


