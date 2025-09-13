cmake_minimum_required(VERSION 3.14)

project(IPC LANGUAGES CXX)

option(LIBIPC_BUILD_DEMOS "Build all of libipc's own demos." OFF)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(IPC_TARGET_NAME ipcInterface)
set(SERVER_TARGET_NAME server)
set(CLIENT_TARGET_NAME client)

find_package(Qt5 REQUIRED COMPONENTS Core Network)

include(GNUInstallDirs)

add_subdirectory(IPCInterface)
if (LIBIPC_BUILD_DEMOS)
	add_subdirectory(app)
endif()
