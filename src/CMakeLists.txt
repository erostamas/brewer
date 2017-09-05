include_directories(common)

add_subdirectory(common)
add_subdirectory(communication)

add_library(brewer_library STATIC
    UnixDomainSocketInterface.cc
    ProcessControl.cc
    CurveStore.cc
    Segment.cc
)

target_link_libraries(brewer_library
    ${BOOST_LIBS}
    brewer_common
)

add_executable(brewer
    main.cc
)

target_link_libraries(brewer
    brewer_library
)
