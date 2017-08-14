#include <gmock/gmock.h>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>

#include "CurveStore.h"

using namespace boost::filesystem;

class TestCurveStore : public ::testing::Test {
public:
    TestCurveStore() {
        createTestDirectory();
        createTestCurveFile();
    }

    ~TestCurveStore() {
        removeTestDirectory();
    }

    void createTestDirectory(void) {
        remove_all(_testDirectoryPath);
        create_directories(_testDirectoryPath);
    }

    void removeTestDirectory(void) {
        remove_all(_testDirectoryPath);
    }

    void createTestCurveFile() {
        std::ofstream curve_file_out;
        curve_file_out.open (getTestCurveFilePath());
        curve_file_out << "testcurve1 1:2;3:4;5:6\n";
        curve_file_out << "testcurve2 7:8;9:10;11:12\n";
        curve_file_out << "testcurve3 13:14;15:16;17:18\n";
        curve_file_out << "disznosajt";
    }

    std::string getTestCurveFilePath() {
        return _testDirectoryPath + _testCurveFileName;
    }

    const std::string _testDirectoryPath = "/tmp/brewer_test_dir/";
    const std::string _testCurveFileName = "curves.txt";

    CurveStore _curveStore;
};

TEST_F(TestCurveStore, test_get_curve_names) {
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "1:2;2:3;4:5"));
    EXPECT_EQ(true, _curveStore.addCurve("curve2", "1:2;2:3;4:5"));
    EXPECT_EQ(true, _curveStore.addCurve("curve3", "1:2;2:3;4:5"));
    EXPECT_EQ(false, _curveStore.addCurve("curve4", "1:a"));

    ASSERT_TRUE(3 == _curveStore.getSize());
    EXPECT_EQ("curves: curve1;curve2;curve3", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string) {
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "1:2;3:4;5:6"));

    ASSERT_TRUE(1 == _curveStore.getSize());
    EXPECT_EQ("curves: curve1", _curveStore.getCurveNames());
    EXPECT_EQ(1, _curveStore._curves["curve1"]->at(0)->getSetpoint());
    EXPECT_EQ(2, _curveStore._curves["curve1"]->at(0)->getDuration());
    EXPECT_EQ(3, _curveStore._curves["curve1"]->at(1)->getSetpoint());
    EXPECT_EQ(4, _curveStore._curves["curve1"]->at(1)->getDuration());
    EXPECT_EQ(5, _curveStore._curves["curve1"]->at(2)->getSetpoint());
    EXPECT_EQ(6, _curveStore._curves["curve1"]->at(2)->getDuration());
}

TEST_F(TestCurveStore, test_add_curve_from_string_with_same_name) {
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "1:2;3:4;5:6"));
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "7:8;9:10;11:12"));

    ASSERT_TRUE(1 == _curveStore.getSize());
    EXPECT_EQ("curves: curve1", _curveStore.getCurveNames());
    EXPECT_EQ(7, _curveStore._curves["curve1"]->at(0)->getSetpoint());
    EXPECT_EQ(8, _curveStore._curves["curve1"]->at(0)->getDuration());
    EXPECT_EQ(9, _curveStore._curves["curve1"]->at(1)->getSetpoint());
    EXPECT_EQ(10, _curveStore._curves["curve1"]->at(1)->getDuration());
    EXPECT_EQ(11, _curveStore._curves["curve1"]->at(2)->getSetpoint());
    EXPECT_EQ(12, _curveStore._curves["curve1"]->at(2)->getDuration());
}

TEST_F(TestCurveStore, test_add_curve_from_string_bullshit) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "disznosajt"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_invalid_setpoint) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "a:2"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_invalid_duration) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "1:b"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_no_duration) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "1:"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_no_duration_2) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "1:2;3:4;5:"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_no_setpoint) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", ":2"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_add_curve_from_string_no_setpoint_2) {
    EXPECT_EQ(false, _curveStore.addCurve("curve1", "1:2;2:3;:5"));

    ASSERT_TRUE(0 == _curveStore.getSize());
    EXPECT_EQ("", _curveStore.getCurveNames());
}

TEST_F(TestCurveStore, test_get_curve) {
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "1:2;2:3;4:5"));

    ASSERT_TRUE(1 == _curveStore.getSize());
    EXPECT_EQ("curves: curve1", _curveStore.getCurveNames());
    CurvePtr curve = _curveStore.getCurve("curve1");
    EXPECT_EQ(1, curve->at(0)->getSetpoint());
    EXPECT_EQ(2, curve->at(0)->getDuration());
    EXPECT_EQ(2, curve->at(1)->getSetpoint());
    EXPECT_EQ(3, curve->at(1)->getDuration());
    EXPECT_EQ(4, curve->at(2)->getSetpoint());
    EXPECT_EQ(5, curve->at(2)->getDuration());
}

TEST_F(TestCurveStore, test_get_curve_non_existing_curve) {
    EXPECT_EQ(true, _curveStore.addCurve("curve1", "1:2;2:3;4:5"));

    ASSERT_TRUE(1 == _curveStore.getSize());
    CurvePtr curve = _curveStore.getCurve("curve2");
    EXPECT_TRUE(!curve);
}

TEST_F(TestCurveStore, test_init_curves_from_test_file) {
    _curveStore.initCurvesFromFile(getTestCurveFilePath());

    ASSERT_TRUE(3 == _curveStore.getSize());
    EXPECT_EQ("curves: testcurve1;testcurve2;testcurve3", _curveStore.getCurveNames());

    EXPECT_EQ(1, _curveStore._curves["testcurve1"]->at(0)->getSetpoint());
    EXPECT_EQ(2, _curveStore._curves["testcurve1"]->at(0)->getDuration());
    EXPECT_EQ(3, _curveStore._curves["testcurve1"]->at(1)->getSetpoint());
    EXPECT_EQ(4, _curveStore._curves["testcurve1"]->at(1)->getDuration());
    EXPECT_EQ(5, _curveStore._curves["testcurve1"]->at(2)->getSetpoint());
    EXPECT_EQ(6, _curveStore._curves["testcurve1"]->at(2)->getDuration());

    EXPECT_EQ(7, _curveStore._curves["testcurve2"]->at(0)->getSetpoint());
    EXPECT_EQ(8, _curveStore._curves["testcurve2"]->at(0)->getDuration());
    EXPECT_EQ(9, _curveStore._curves["testcurve2"]->at(1)->getSetpoint());
    EXPECT_EQ(10, _curveStore._curves["testcurve2"]->at(1)->getDuration());
    EXPECT_EQ(11, _curveStore._curves["testcurve2"]->at(2)->getSetpoint());
    EXPECT_EQ(12, _curveStore._curves["testcurve2"]->at(2)->getDuration());

    EXPECT_EQ(13, _curveStore._curves["testcurve3"]->at(0)->getSetpoint());
    EXPECT_EQ(14, _curveStore._curves["testcurve3"]->at(0)->getDuration());
    EXPECT_EQ(15, _curveStore._curves["testcurve3"]->at(1)->getSetpoint());
    EXPECT_EQ(16, _curveStore._curves["testcurve3"]->at(1)->getDuration());
    EXPECT_EQ(17, _curveStore._curves["testcurve3"]->at(2)->getSetpoint());
    EXPECT_EQ(18, _curveStore._curves["testcurve3"]->at(2)->getDuration());
}

TEST_F(TestCurveStore, test_init_curves_from_non_existing_test_file) {
    _curveStore.initCurvesFromFile("disznosajt");

    ASSERT_TRUE(0 == _curveStore.getSize());
}

TEST_F(TestCurveStore, test_save_curves_to_file) {
    _curveStore.initCurvesFromFile(getTestCurveFilePath());
    remove(getTestCurveFilePath());
    _curveStore.saveCurvesToFile(getTestCurveFilePath());
    _curveStore._curves.clear();
    _curveStore.initCurvesFromFile(getTestCurveFilePath());

    ASSERT_TRUE(3 == _curveStore.getSize());
    EXPECT_EQ("curves: testcurve1;testcurve2;testcurve3", _curveStore.getCurveNames());

    EXPECT_EQ(1, _curveStore._curves["testcurve1"]->at(0)->getSetpoint());
    EXPECT_EQ(2, _curveStore._curves["testcurve1"]->at(0)->getDuration());
    EXPECT_EQ(3, _curveStore._curves["testcurve1"]->at(1)->getSetpoint());
    EXPECT_EQ(4, _curveStore._curves["testcurve1"]->at(1)->getDuration());
    EXPECT_EQ(5, _curveStore._curves["testcurve1"]->at(2)->getSetpoint());
    EXPECT_EQ(6, _curveStore._curves["testcurve1"]->at(2)->getDuration());

    EXPECT_EQ(7, _curveStore._curves["testcurve2"]->at(0)->getSetpoint());
    EXPECT_EQ(8, _curveStore._curves["testcurve2"]->at(0)->getDuration());
    EXPECT_EQ(9, _curveStore._curves["testcurve2"]->at(1)->getSetpoint());
    EXPECT_EQ(10, _curveStore._curves["testcurve2"]->at(1)->getDuration());
    EXPECT_EQ(11, _curveStore._curves["testcurve2"]->at(2)->getSetpoint());
    EXPECT_EQ(12, _curveStore._curves["testcurve2"]->at(2)->getDuration());

    EXPECT_EQ(13, _curveStore._curves["testcurve3"]->at(0)->getSetpoint());
    EXPECT_EQ(14, _curveStore._curves["testcurve3"]->at(0)->getDuration());
    EXPECT_EQ(15, _curveStore._curves["testcurve3"]->at(1)->getSetpoint());
    EXPECT_EQ(16, _curveStore._curves["testcurve3"]->at(1)->getDuration());
    EXPECT_EQ(17, _curveStore._curves["testcurve3"]->at(2)->getSetpoint());
    EXPECT_EQ(18, _curveStore._curves["testcurve3"]->at(2)->getDuration());
}

TEST_F(TestCurveStore, test_save_curves_to_file_overwrite_existing) {
    _curveStore.initCurvesFromFile(getTestCurveFilePath());
    _curveStore.saveCurvesToFile(getTestCurveFilePath());
    _curveStore.saveCurvesToFile(getTestCurveFilePath());
    _curveStore.saveCurvesToFile(getTestCurveFilePath());
    _curveStore._curves.clear();
    _curveStore.initCurvesFromFile(getTestCurveFilePath());

    ASSERT_TRUE(3 == _curveStore.getSize());
    EXPECT_EQ("curves: testcurve1;testcurve2;testcurve3", _curveStore.getCurveNames());

    EXPECT_EQ(1, _curveStore._curves["testcurve1"]->at(0)->getSetpoint());
    EXPECT_EQ(2, _curveStore._curves["testcurve1"]->at(0)->getDuration());
    EXPECT_EQ(3, _curveStore._curves["testcurve1"]->at(1)->getSetpoint());
    EXPECT_EQ(4, _curveStore._curves["testcurve1"]->at(1)->getDuration());
    EXPECT_EQ(5, _curveStore._curves["testcurve1"]->at(2)->getSetpoint());
    EXPECT_EQ(6, _curveStore._curves["testcurve1"]->at(2)->getDuration());

    EXPECT_EQ(7, _curveStore._curves["testcurve2"]->at(0)->getSetpoint());
    EXPECT_EQ(8, _curveStore._curves["testcurve2"]->at(0)->getDuration());
    EXPECT_EQ(9, _curveStore._curves["testcurve2"]->at(1)->getSetpoint());
    EXPECT_EQ(10, _curveStore._curves["testcurve2"]->at(1)->getDuration());
    EXPECT_EQ(11, _curveStore._curves["testcurve2"]->at(2)->getSetpoint());
    EXPECT_EQ(12, _curveStore._curves["testcurve2"]->at(2)->getDuration());

    EXPECT_EQ(13, _curveStore._curves["testcurve3"]->at(0)->getSetpoint());
    EXPECT_EQ(14, _curveStore._curves["testcurve3"]->at(0)->getDuration());
    EXPECT_EQ(15, _curveStore._curves["testcurve3"]->at(1)->getSetpoint());
    EXPECT_EQ(16, _curveStore._curves["testcurve3"]->at(1)->getDuration());
    EXPECT_EQ(17, _curveStore._curves["testcurve3"]->at(2)->getSetpoint());
    EXPECT_EQ(18, _curveStore._curves["testcurve3"]->at(2)->getDuration());
}
