#include "StringCommandAdapter.h"

#include "SetpointCommand.h"
#include "DeltaSetpointCommand.h"

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
            /*} else if (message.substr(0, 15) == "get_temperature"){
                std::string temp = "temp: " + std::to_string(_currentTemperature) + "\n";
                _tcpInterface->sendMessage(temp);
            } else if (message.substr(0, 12) == "get_setpoint"){
                std::string setpoint_str = "sp: " + std::to_string(_setpoint) + "\n";
                _tcpInterface->sendMessage(setpoint_str); */
            } else if (commandString.substr(0, 12) == "inc_setpoint"){
                ret.emplace_back(new DeltaSetpointCommand(1));
            } else if (commandString.substr(0, 12) == "dec_setpoint"){
                ret.emplace_back(new DeltaSetpointCommand(-1));
            }/*  else if (message.substr(0, 9) == "playcurve"){
                playCurve(message.substr(10, message.length()));
            } else if (message.substr(0, 10) == "get_curves"){
                _tcpInterface->sendMessage(_curveStore.getCurveNames() + "\n");
            } */
    }
    return ret;
}