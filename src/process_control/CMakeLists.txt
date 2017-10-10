add_library(brewer_library STATIC
    ProcessControl.cc
    CurveStore.cc
    Segment.cc
    ProcessVariableBase.cc
    ProcessVariableStore.cc
    XmlSerializer.cc
    StringCommandAdapter.cc
)

target_link_libraries(brewer_library
    ${BOOST_LIBS}
    brewer_common
    udp_communication
    wiringPi
)

add_subdirectory(test)