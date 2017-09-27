add_library(brewer_library STATIC
    ProcessControl.cc
    CurveStore.cc
    Segment.cc
)

target_link_libraries(brewer_library
    ${BOOST_LIBS}
    brewer_common
    udp_communication
    wiringPi
)