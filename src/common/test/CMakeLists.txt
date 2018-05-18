set (TESTNAME test_brewer_common)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(${TESTNAME}
    TestConfig.cc)

target_link_libraries(${TESTNAME}
    brewer_library
    boost_log
    boost_thread
    boost_system
    boost_filesystem
    gmock
    gmock_main)