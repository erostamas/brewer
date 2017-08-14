set (TESTNAME test_brewer)
include_directories(../src)

add_executable(${TESTNAME}
    TestCurveStore.cc
    TestSegment.cc)

target_link_libraries(${TESTNAME}
    brewer_library
    boost_log
    boost_thread
    boost_system
    boost_filesystem
    gmock
    gmock_main)