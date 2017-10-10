#include <gmock/gmock.h>

#include "ProcessControl.h"
#include "SetpointCommand.h"
#include "DeltaSetpointCommand.h"

TEST(TestProcessControl, test_setpoint_command) {
    ProcessControl pc;
    SetpointCommand setpointCommand(53.0);
    setpointCommand.execute(pc);
    EXPECT_EQ(pc.getSetpoint().get(), 53.0);
}

TEST(TestProcessControl, test_increase_setpoint_command) {
    ProcessControl pc;
    SetpointCommand setpointCommand(53.0);
    setpointCommand.execute(pc);
    DeltaSetpointCommand increaseSetpointCommand(1);
    increaseSetpointCommand.execute(pc);
    EXPECT_EQ(pc.getSetpoint().get(), 54.0);
}

TEST(TestProcessControl, test_decrease_setpoint_command) {
    ProcessControl pc;
    SetpointCommand setpointCommand(53.0);
    setpointCommand.execute(pc);
    DeltaSetpointCommand decreaseSetpointCommand(-1);
    decreaseSetpointCommand.execute(pc);
    EXPECT_EQ(pc.getSetpoint().get(), 52.0);
}
