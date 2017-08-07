set (TESTNAME test_brewer)
include_directories(../src)

add_executable(${TESTNAME}
    TestMain.cc
    TestSegment.cc
    TestTcpInterface.cc)

target_link_libraries(${TESTNAME}
    brewer_library
    boost_unit_test_framework
    boost_log
    boost_thread
    boost_system
    boost_filesystem)

add_test(${TESTNAME} ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME})

add_executable(test_gmock
    TestCurveStore.cc
    Test.cc)

target_link_libraries(test_gmock
    brewer_library
    boost_log
    boost_thread
    boost_system
    boost_filesystem
    gmock
    gmock_main)