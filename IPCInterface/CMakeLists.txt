add_library(${LIBRARY_TARGET_NAME} SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/include/clientInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/serverInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IpcEndpoint.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ipcMessage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/global.hpp
)

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientProxy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverProxy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientInternal.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverInternal.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/circularQueue.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.hpp
)

target_sources(${LIBRARY_TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ipcMessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverInternal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clientProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serverProxy.cpp
)

target_compile_definitions(${LIBRARY_TARGET_NAME} PRIVATE IPC_LIBRARY)

target_include_directories(${LIBRARY_TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC
    Qt5::Core
    Qt5::Network
    Qt5::Xml
    Qt5::Widgets
)

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
