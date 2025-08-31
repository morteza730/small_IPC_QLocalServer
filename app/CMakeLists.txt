add_executable(${SERVER_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
)

target_link_libraries(${SERVER_TARGET_NAME} PUBLIC
    Qt5::Core
    ${IPC_TARGET_NAME}
)

set_target_properties(${SERVER_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_executable(${CLIENT_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
)

target_link_libraries(${CLIENT_TARGET_NAME} PUBLIC
Qt5::Core
${IPC_TARGET_NAME}
)

set_target_properties(${CLIENT_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)