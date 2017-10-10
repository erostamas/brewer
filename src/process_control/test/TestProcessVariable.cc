#include <gmock/gmock.h>

#include "ProcessVariable.h"
#include "ProcessVariableStore.h"

TEST(TestProcessVariable, test_double_assignment) {
    ProcessVariable<TYPE::DOUBLE> x("varname", Accessibility::READWRITE);
    x = 5.5;
    EXPECT_TRUE(x == 5.5);
    EXPECT_EQ(1, ProcessVariableStore::_variables.size());
}

TEST(TestProcessVariable, test_string_assignment) {
    ProcessVariable<TYPE::STRING> x("varname", Accessibility::READWRITE);
    x = "value";
    EXPECT_TRUE(x == "value");
}
