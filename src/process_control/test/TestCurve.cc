#include <gmock/gmock.h>

#include "Curve.h"
#include "Exceptions.h"

TEST(TestCurve, test_curve_valid_1) {
    Curve c("curve", "12.3:55");
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ("12.30:55", c.toString());
}

TEST(TestCurve, test_curve_valid_2) {
    Curve c("curve", "12.3:55;56.4:32");
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ("12.30:55;56.40:32", c.toString());
}

TEST(TestCurve, test_curve_invalid_curve_1) {
    EXPECT_THROW(Curve c("curve", ""), CurveParseError);
}

TEST(TestCurve, test_curve_invalid_curve_2) {
    EXPECT_THROW(Curve c("curve", ";;"), CurveParseError);
}

TEST(TestCurve, test_curve_invalid_segment_1) {
    EXPECT_THROW(Curve c("curve", "12.3:;56.4:32"), SegmentParseError);
}
