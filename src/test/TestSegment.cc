#include <gmock/gmock.h>

#include "Segment.h"

TEST(TestSegment, test_segment_default_constructor) {
    Segment s;
    EXPECT_EQ(0.0, s.getSetpoint());
    EXPECT_EQ(0.0, s.getDuration());
}

TEST(TestSegment, test_segment_setsetpoint) {
    Segment s;
    s.setSetpoint(1.2);

    EXPECT_EQ(1.2, s.getSetpoint());
}

TEST(TestSegment, test_segment_setduration) {
    Segment s;
    s.setDuration(2);

    EXPECT_EQ(2, s.getDuration());
}

TEST(TestSegment, test_segment_tostring) {
    Segment s;
    s.setSetpoint(1.2);
    s.setDuration(2);
    EXPECT_EQ("1.20:2", s.toString());
}
