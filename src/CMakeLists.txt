add_library(brewer_library STATIC
    TcpInterface.cc
    ProcessControl.cc
    CurveStore.cc
)

add_executable(brewer
    main.cc)

target_link_libraries(brewer
    brewer_library)

