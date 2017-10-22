#include "StringCommandAdapter.h"

#include "SetpointCommand.h"
#include "DeltaSetpointCommand.h"
#include "ShutdownCommand.h"

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
            } /*else if (message.substr(0, 9) == "playcurve"){
                playCurve(message.substr(10, message.length()));
            }*/
    }
    return ret;
}