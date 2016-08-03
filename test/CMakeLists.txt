set (TESTNAME test_brewer)  

add_executable(${TESTNAME}
    TestMain.cc
    TestCurveStore.cc)

target_link_libraries(${TESTNAME}
    boost_unit_test_framework)

add_test(${TESTNAME} ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME})