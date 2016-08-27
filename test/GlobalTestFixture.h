#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>

using namespace boost::filesystem;

class GlobalTestFixture{
public:
    GlobalTestFixture() {
        std::cout << "Creating test input files"<< std::endl;
        createTestDirectory();
        createTestCurveFile();
    }
    
    ~GlobalTestFixture() {
        std::cout << "Removing test input files"<< std::endl;
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
    
    static std::string getTestCurveFilePath() {
        return _testDirectoryPath + _testCurveFileName;
    }
    
    static const std::string _testDirectoryPath;
    static const std::string _testCurveFileName;
};