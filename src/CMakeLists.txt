#testing gerrithub

add_library(brewer_library STATIC
    TcpInterface.cc
    UnixDomainSocketInterface.cc
    ProcessControl.cc
    CurveStore.cc
    Segment.cc
    Logging.cc
)
target_link_libraries(brewer_library
    boost_log
    boost_thread
    boost_system)

add_executable(brewer
    main.cc)

target_link_libraries(brewer
    brewer_library)

