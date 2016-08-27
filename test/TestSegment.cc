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

BOOST_AUTO_TEST_CASE(test_set_setpoint) {
    setSetpoint(3.4);
    
    BOOST_CHECK_EQUAL(3.4, getSetpoint());
}

BOOST_AUTO_TEST_SUITE_END()