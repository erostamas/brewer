#include <iostream>
#include <unistd.h>

#include "UdpInterface.h"
#include "Logging.h"

int main() {
    init_logging();
    UdpInterface udp(50001);
    std::string msg;
    while (true) {
        sleep(1);
    }
}