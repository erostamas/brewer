#include <gmock/gmock.h>
#include <string>

#include "Config.h"

static constexpr const char* TEST_CONFIG_1 = R"(
{
    "stringkey": "value",
    "integerkey": 100,
    "boolkey": true
}
)";

TEST(TestConfig, test_simple_values) {
    std::istringstream iss(TEST_CONFIG_1);
    Config cfg(iss);
    EXPECT_EQ("value", cfg.get("stringkey", std::string("default_value")));
    EXPECT_EQ(100, cfg.get("integerkey", 0));
    EXPECT_EQ(true, cfg.get("boolkey", false));
}

TEST(TestConfig, test_non_existing_value) {
    std::istringstream iss(TEST_CONFIG_1);
    Config cfg(iss);
    EXPECT_EQ("", cfg.get("kolbasz", std::string("")));
}

