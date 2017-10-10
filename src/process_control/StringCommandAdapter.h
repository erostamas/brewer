#pragma once

#include "ICommandAdapter.h"
#include "UdpInterface.h"

class StringCommandAdapter : public ICommandAdapter {
public:
    StringCommandAdapter();

    void startCommandReceiver() override;
    std::vector<std::unique_ptr<ICommand>> getCommands() const override;

private:
    std::unique_ptr<UdpInterface> _udpInterface;
};