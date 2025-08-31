
set(VERIFIED_CLIENT false)

set(CMAKE_AUTOMOC ON)

add_library(${IPC_TARGET_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/include/clientInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/serverInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ipcMessage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IpcEndpoint.hpp
)

target_sources(${IPC_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/clientProxy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/serverProxy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/clientInternal.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/serverInternal.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/circularQueue.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utility.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ipcExport.hpp
)

target_sources(${IPC_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ipcMessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverInternal.cpp
)

target_include_directories(${IPC_TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${IPC_TARGET_NAME} PUBLIC
    Qt5::Core
    Qt5::Network
)

target_compile_definitions(${IPC_TARGET_NAME} PRIVATE IPC_LIBRARY)


configure_file(
        "config.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)

set_target_properties(${IPC_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
