
set(VERIFIED_CLIENT false)

set(CMAKE_AUTOMOC ON)

file(GLOB HEAD_FILES
    ${LIBIPC_PROJECT_DIR}/include/IPCInterface/*.hpp
)

file(GLOB SRC_FILES
    ${LIBIPC_PROJECT_DIR}/src/IPCInterface/*.hpp
    ${LIBIPC_PROJECT_DIR}/src/IPCInterface/*.cpp
)

add_library(${IPC_TARGET_NAME} SHARED ${HEAD_FILES})

target_sources(${IPC_TARGET_NAME} PRIVATE
    ${SRC_FILES}
)

target_link_libraries(${IPC_TARGET_NAME} PUBLIC
    Qt5::Core
    Qt5::Network
)

target_compile_definitions(${IPC_TARGET_NAME} PRIVATE IPC_LIBRARY)

configure_file(
        "config.h.in"
        "${LIBIPC_PROJECT_DIR}/src/IPCInterface/config.h" ESCAPE_QUOTES
)

set_target_properties(${IPC_TARGET_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/libs
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/libs
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/libs
)

target_include_directories(${IPC_TARGET_NAME}
  PUBLIC
    ${LIBIPC_PROJECT_DIR}/include
)

target_include_directories(${IPC_TARGET_NAME}
  PRIVATE
    ${LIBIPC_PROJECT_DIR}/include/IPCInterface
)
