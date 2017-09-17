include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/communication/udp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/communication/unix_socket)


add_subdirectory(common)
add_subdirectory(test)

add_library(brewer_library STATIC
    ProcessControl.cc
    CurveStore.cc
    Segment.cc
)

target_link_libraries(brewer_library
    ${BOOST_LIBS}
    brewer_common
    udp_communication
)

add_executable(brewer
    main.cc
)

target_link_libraries(brewer
    brewer_library
)
