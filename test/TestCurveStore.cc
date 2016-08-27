#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "CurveStore.h"
#include "GlobalTestFixture.h"

class TestCurveStore : public CurveStore{
public:
    TestCurveStore() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }
};

BOOST_FIXTURE_TEST_SUITE(curve_store_test_suite, TestCurveStore)

BOOST_AUTO_TEST_CASE(test_get_curve_names) {
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "1:2;2:3;4:5"));
    BOOST_CHECK_EQUAL(true, addCurve("curve2", "1:2;2:3;4:5"));
    BOOST_CHECK_EQUAL(true, addCurve("curve3", "1:2;2:3;4:5"));
    BOOST_CHECK_EQUAL(false, addCurve("curve4", "1:a"));

    BOOST_REQUIRE(3 == getSize());
    BOOST_CHECK_EQUAL("curves: curve1;curve2;curve3", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string) {
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "1:2;3:4;5:6"));

    BOOST_REQUIRE(1 == getSize());
    BOOST_CHECK_EQUAL("curves: curve1", getCurveNames());
    BOOST_CHECK_EQUAL(1, _curves["curve1"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(2, _curves["curve1"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(3, _curves["curve1"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(4, _curves["curve1"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(5, _curves["curve1"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(6, _curves["curve1"]->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_with_same_name) {
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "1:2;3:4;5:6"));
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "7:8;9:10;11:12"));

    BOOST_REQUIRE(1 == getSize());
    BOOST_CHECK_EQUAL("curves: curve1", getCurveNames());
    BOOST_CHECK_EQUAL(7, _curves["curve1"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(8, _curves["curve1"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(9, _curves["curve1"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(10, _curves["curve1"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(11, _curves["curve1"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(12, _curves["curve1"]->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_bullshit) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "disznosajt"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_invalid_setpoint) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "a:2"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_invalid_duration) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "1:b"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_no_duration) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "1:"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_no_duration_2) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "1:2;3:4;5:"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_no_setpoint) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", ":2"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_add_curve_from_string_no_setpoint_2) {
    BOOST_CHECK_EQUAL(false, addCurve("curve1", "1:2;2:3;:5"));

    BOOST_REQUIRE(0 == getSize());
    BOOST_CHECK_EQUAL("", getCurveNames());
}

BOOST_AUTO_TEST_CASE(test_get_curve) {
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "1:2;2:3;4:5"));

    BOOST_REQUIRE(1 == getSize());
    BOOST_CHECK_EQUAL("curves: curve1", getCurveNames());
    CurvePtr curve = getCurve("curve1");
    BOOST_CHECK_EQUAL(1, curve->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(2, curve->at(0)->getDuration());
    BOOST_CHECK_EQUAL(2, curve->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(3, curve->at(1)->getDuration());
    BOOST_CHECK_EQUAL(4, curve->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(5, curve->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(test_get_curve_non_existing_curve) {
    BOOST_CHECK_EQUAL(true, addCurve("curve1", "1:2;2:3;4:5"));

    BOOST_REQUIRE(1 == getSize());
    CurvePtr curve = getCurve("curve2");
    BOOST_CHECK(!curve);
}

BOOST_AUTO_TEST_CASE(test_init_curves_from_test_file) {
    initCurvesFromFile(GlobalTestFixture::getTestCurveFilePath());

    BOOST_REQUIRE(3 == getSize());
    BOOST_CHECK_EQUAL("curves: testcurve1;testcurve2;testcurve3", getCurveNames());

    BOOST_CHECK_EQUAL(1, _curves["testcurve1"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(2, _curves["testcurve1"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(3, _curves["testcurve1"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(4, _curves["testcurve1"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(5, _curves["testcurve1"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(6, _curves["testcurve1"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(7, _curves["testcurve2"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(8, _curves["testcurve2"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(9, _curves["testcurve2"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(10, _curves["testcurve2"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(11, _curves["testcurve2"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(12, _curves["testcurve2"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(13, _curves["testcurve3"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(14, _curves["testcurve3"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(15, _curves["testcurve3"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(16, _curves["testcurve3"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(17, _curves["testcurve3"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(18, _curves["testcurve3"]->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(test_init_curves_from_non_existing_test_file) {
    initCurvesFromFile("disznosajt");

    BOOST_REQUIRE(0 == getSize());
}

BOOST_AUTO_TEST_CASE(test_save_curves_to_file) {
    initCurvesFromFile(GlobalTestFixture::getTestCurveFilePath());
    remove(GlobalTestFixture::getTestCurveFilePath());
    saveCurvesToFile(GlobalTestFixture::getTestCurveFilePath());
    _curves.clear();
    initCurvesFromFile(GlobalTestFixture::getTestCurveFilePath());
    
    BOOST_REQUIRE(3 == getSize());
    BOOST_CHECK_EQUAL("curves: testcurve1;testcurve2;testcurve3", getCurveNames());

    BOOST_CHECK_EQUAL(1, _curves["testcurve1"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(2, _curves["testcurve1"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(3, _curves["testcurve1"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(4, _curves["testcurve1"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(5, _curves["testcurve1"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(6, _curves["testcurve1"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(7, _curves["testcurve2"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(8, _curves["testcurve2"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(9, _curves["testcurve2"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(10, _curves["testcurve2"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(11, _curves["testcurve2"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(12, _curves["testcurve2"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(13, _curves["testcurve3"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(14, _curves["testcurve3"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(15, _curves["testcurve3"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(16, _curves["testcurve3"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(17, _curves["testcurve3"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(18, _curves["testcurve3"]->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(test_save_curves_to_file_overwrite_existing) {
    initCurvesFromFile(GlobalTestFixture::getTestCurveFilePath());
    saveCurvesToFile(GlobalTestFixture::getTestCurveFilePath());
    saveCurvesToFile(GlobalTestFixture::getTestCurveFilePath());
    saveCurvesToFile(GlobalTestFixture::getTestCurveFilePath());
    _curves.clear();
    initCurvesFromFile(GlobalTestFixture::getTestCurveFilePath());
    
    BOOST_REQUIRE(3 == getSize());
    BOOST_CHECK_EQUAL("curves: testcurve1;testcurve2;testcurve3", getCurveNames());

    BOOST_CHECK_EQUAL(1, _curves["testcurve1"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(2, _curves["testcurve1"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(3, _curves["testcurve1"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(4, _curves["testcurve1"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(5, _curves["testcurve1"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(6, _curves["testcurve1"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(7, _curves["testcurve2"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(8, _curves["testcurve2"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(9, _curves["testcurve2"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(10, _curves["testcurve2"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(11, _curves["testcurve2"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(12, _curves["testcurve2"]->at(2)->getDuration());

    BOOST_CHECK_EQUAL(13, _curves["testcurve3"]->at(0)->getSetpoint());
    BOOST_CHECK_EQUAL(14, _curves["testcurve3"]->at(0)->getDuration());
    BOOST_CHECK_EQUAL(15, _curves["testcurve3"]->at(1)->getSetpoint());
    BOOST_CHECK_EQUAL(16, _curves["testcurve3"]->at(1)->getDuration());
    BOOST_CHECK_EQUAL(17, _curves["testcurve3"]->at(2)->getSetpoint());
    BOOST_CHECK_EQUAL(18, _curves["testcurve3"]->at(2)->getDuration());
}

BOOST_AUTO_TEST_CASE(testcase1) {

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()