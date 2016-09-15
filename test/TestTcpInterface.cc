#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <thread>

#include "TcpInterface.h"
#include "GlobalTestFixture.h"

class TestTcpInterface : public TcpInterface{
public:
    TestTcpInterface() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }

};

void startTCPListening(TestTcpInterface* tcpint) {
	tcpint->run();
}

BOOST_FIXTURE_TEST_SUITE(tcpinterface_test_suite, TestTcpInterface)

BOOST_AUTO_TEST_CASE(test_run) {
    //std::thread t1(startTCPListening(this));
    //_shouldExit = true;
}

BOOST_AUTO_TEST_SUITE_END()