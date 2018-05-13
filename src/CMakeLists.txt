include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/communication/udp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/process_control)


add_subdirectory(common)
add_subdirectory(test)
add_subdirectory(process_control)

add_executable(brewer
    main.cc
)

target_link_libraries(brewer
    brewer_library
    boost_program_options
)

INSTALL(TARGETS brewer
        DESTINATION /opt/erostamas/brewer
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_WRITE GROUP_READ)