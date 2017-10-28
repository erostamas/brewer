#include <gmock/gmock.h>

#include "Segment.h"
#include "Exceptions.h"

TEST(TestSegment, test_segment_valid_1) {
    Segment s("12.3:55");
    EXPECT_EQ(s.getSetpoint(), 12.3);
    EXPECT_EQ(s.getDuration(), 55);
    EXPECT_EQ("12.30:55", s.toString());
}

TEST(TestSegment, test_segment_valid_2) {
    Segment s("12:55.6");
    EXPECT_EQ(s.getSetpoint(), 12);
    EXPECT_EQ(s.getDuration(), 55);
    EXPECT_EQ("12.00:55", s.toString());
}

TEST(TestSegment, test_segment_invalid_segment) {
    EXPECT_THROW(Segment s("blabla"), SegmentParseError);
}

TEST(TestSegment, test_segment_invalid_segment_2) {
    EXPECT_THROW(Segment s(":"), SegmentParseError);
}

TEST(TestSegment, test_segment_invalid_segment_3) {
    EXPECT_THROW(Segment s("12:"), SegmentParseError);
}

TEST(TestSegment, test_segment_invalid_setpoint) {
    EXPECT_THROW(Segment s("lulu:55"), SegmentParseError);
}

TEST(TestSegment, test_segment_invalid_duration) {
    EXPECT_THROW(Segment s("12.3:lulu"), SegmentParseError);
}
