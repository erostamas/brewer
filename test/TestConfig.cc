#include <gmock/gmock.h>

#include "Config.h"

static constexpr const char* TEST_CONFIG_1 = "{\"stringkey\": \"value\", \"integerkey\": 100}";

TEST(TestConfig, test_simple_values) {
    std::istringstream iss(TEST_CONFIG_1);
    Config cfg(iss);
    EXPECT_EQ("value", cfg.getString("stringkey"));
    EXPECT_EQ(100, cfg.getInteger("integerkey"));
}

