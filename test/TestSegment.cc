#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Segment.h"
#include "GlobalTestFixture.h"

class TestSegment : public Segment{
public:
    TestSegment() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }
};

BOOST_FIXTURE_TEST_SUITE(segment_test_suite, TestSegment)

BOOST_AUTO_TEST_CASE(test_segment_default_constructor) {
    BOOST_CHECK_EQUAL(0.0, getSetpoint());
    BOOST_CHECK_EQUAL(0.0, getDuration());
}

BOOST_AUTO_TEST_CASE(test_segment_setsetpoint) {
    setSetpoint(1.2);

    BOOST_CHECK_EQUAL(1.2, getSetpoint());
}

BOOST_AUTO_TEST_CASE(test_segment_setduration) {
    setDuration(2);

    BOOST_CHECK_EQUAL(2, getDuration());
}

BOOST_AUTO_TEST_CASE(test_segment_tostring) {
    setSetpoint(1.2);
    setDuration(2);
    BOOST_CHECK_EQUAL("1.20:2", toString());
}

BOOST_AUTO_TEST_SUITE_END()