cmake_minimum_required(VERSION 3.14)

project(IPC LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_TARGET_NAME ipcInterface)
set(APPLICATION_TARGET_NAME ipcTester)

find_package(Qt5 REQUIRED COMPONENTS Core Xml Network Widgets)

add_subdirectory(IPCInterface)
add_subdirectory(app)

include(GNUInstallDirs)
