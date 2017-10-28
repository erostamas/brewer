#include <gmock/gmock.h>

#include "CurvePlayer.h"
#include "FakeSystem.h"

TEST(TestCurvePlayer, test_curve_1) {
    CurvePtr curve = std::make_shared<Curve>("curve", "12.3:55;56.7:60");
    std::shared_ptr<FakeSystem> system = std::make_shared<FakeSystem>();
    CurvePlayer curvePlayer(system);
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::IDLE);

    curvePlayer.playCurve(curve);
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::RUNNING);
    EXPECT_EQ(curvePlayer.getCurrentSetpoint(), 12.3);

    curvePlayer.step();
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::RUNNING);
    EXPECT_EQ(curvePlayer.getCurrentSetpoint(), 12.3);

    system->sleep(50);
    curvePlayer.step();
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::RUNNING);
    EXPECT_EQ(curvePlayer.getCurrentSetpoint(), 12.3);

    system->sleep(6);
    curvePlayer.step();
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::RUNNING);
    EXPECT_EQ(curvePlayer.getCurrentSetpoint(), 56.7);

    system->sleep(60);
    curvePlayer.step();
    EXPECT_EQ(curvePlayer.getState(), CurvePlayerState::IDLE);
    EXPECT_EQ(curvePlayer.getCurrentSetpoint(), -1);
}
