add_library(brewer_library STATIC
    ProcessControl.cc
    Segment.cc
    Curve.cc
    CurvePlayer.cc
    ProcessVariableBase.cc
    ProcessVariableStore.cc
    StringCommandAdapter.cc
)

target_link_libraries(brewer_library
    ${BOOST_LIBS}
    brewer_common
    udp_communication
    wiringPi
    cpp_redis
    tacopie
)

add_subdirectory(test)