#include <iostream>
#include <unistd.h>

#include "UdpSender.h"
#include "Logging.h"

int main() {
    init_logging();
    std::string msg = "hellobello";
    while (true) {
        sleep(1);
        UdpSender sender("172.24.1.133", 50002);
        std::string msg = "response LULU";
        sender.send(msg);
    }
}