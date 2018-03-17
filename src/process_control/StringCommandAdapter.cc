#include "StringCommandAdapter.h"

#include "SetpointCommand.h"
#include "DeltaSetpointCommand.h"
#include "ShutdownCommand.h"
#include "PlayCurveCommand.h"
#include "PauseCurveCommand.h"
#include "ResumeCurveCommand.h"
#include "Logging.h"
#include "Utils.h"

StringCommandAdapter::StringCommandAdapter()
: _udpInterface(new UdpInterface(50001)) {
}

void StringCommandAdapter::startCommandReceiver() {
    _udpInterface->startReceiveThread();
}

std::vector<std::unique_ptr<ICommand>> StringCommandAdapter::getCommands() const {
    std::vector<std::unique_ptr<ICommand>> ret;
    for (const auto& command : _udpInterface->getMessages()) {
        std::string commandString(command);
            if (commandString.substr(0, 8) == "setpoint") {
                ret.emplace_back(new SetpointCommand(std::stod(commandString.substr(9, commandString.length()))));
            } else if (commandString.substr(0, 12) == "inc_setpoint"){
                ret.emplace_back(new DeltaSetpointCommand(1));
            } else if (commandString.substr(0, 12) == "dec_setpoint"){
                ret.emplace_back(new DeltaSetpointCommand(-1));
            } else if (commandString == "shutdown"){
                ret.emplace_back(new ShutdownCommand());
            } else if (commandString.substr(0, 9) == "playcurve"){
                try {
                    std::vector<std::string> tokens = Utils::split(commandString.substr(10, commandString.length()), ' ');
                    if (tokens.size() == 2) {
                        CurvePtr curve = std::make_shared<Curve>(tokens[0], tokens[1]);
                        ret.emplace_back(new PlayCurveCommand(curve));
                    } else {
                        LOG_ERROR << "[StringCommandAdapter] Failed to parse playcurve command: " << commandString.substr(10, commandString.length());
                    }
                } catch (std::exception e) {
                    LOG_ERROR << "[StringCommandAdapter] Failed to parse playcurve command - " << e.what();
                }
            } else if (commandString == "pause"){
                ret.emplace_back(new PauseCurveCommand());
            } else if (commandString == "resume"){
                ret.emplace_back(new ResumeCurveCommand());
            }
    }
    return ret;
}