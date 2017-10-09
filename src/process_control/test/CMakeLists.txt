include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(test_process_control
    TestProcessVariable.cc
    TestXmlSerializer.cc
)

target_link_libraries(test_process_control
    gmock
    gmock_main
    pthread
    brewer_library
)
