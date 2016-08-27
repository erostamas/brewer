#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_brewer
#include <boost/test/unit_test.hpp>

#define BOOST_LOG_DYN_LINK 1

#include "GlobalTestFixture.h"

const std::string GlobalTestFixture::_testDirectoryPath = "/tmp/brewer_test_dir/";
const std::string GlobalTestFixture::_testCurveFileName = "curves.txt";

BOOST_GLOBAL_FIXTURE(GlobalTestFixture);