add_library(udp_communication STATIC
    UdpInterface.cc
    UdpReceiver.cc
    UdpSender.cc)

target_link_libraries(udp_communication
    ${BOOST_LIBS}
)