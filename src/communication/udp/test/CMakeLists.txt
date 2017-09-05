add_executable(udp_receiver_test
    udp_receiver_test.cc
)

target_link_libraries(udp_receiver_test
    ${BOOST_LIBS}
    brewer_common
    udp_communication
)