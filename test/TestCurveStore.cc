#include <boost/test/unit_test.hpp>

#include "CurveStore.h"

BOOST_FIXTURE_TEST_SUITE(curve_store_test_suite, CurveStore)

BOOST_AUTO_TEST_CASE(test_add_curve_from_string) {
    addCurve("curve1", "1:2;3:4;5:6");
    BOOST_CHECK_EQUAL(1, getSize());
    BOOST_CHECK_EQUAL("curves: curve1", getCurveNames());
    BOOST_CHECK_EQUAL(1, _curves["curve1"][0].get()->getSetpoint());
    BOOST_CHECK_EQUAL(2, _curves["curve1"][0].get()->getDuration());
    BOOST_CHECK_EQUAL(3, _curves["curve1"][1].get()->getSetpoint());
    BOOST_CHECK_EQUAL(4, _curves["curve1"][1].get()->getDuration());
    BOOST_CHECK_EQUAL(5, _curves["curve1"][2].get()->getSetpoint());
    BOOST_CHECK_EQUAL(6, _curves["curve1"][2].get()->getDuration());
}

BOOST_AUTO_TEST_CASE(testcase1) {

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()