add_library(brewer_library STATIC
    TcpInterface.cc
    ProcessControl.cc
    CurveStore.cc
)
target_link_libraries(brewer_library
    boost_log)

add_executable(brewer
    main.cc)

target_link_libraries(brewer
    brewer_library)

