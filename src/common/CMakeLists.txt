add_subdirectory(communication)

add_library(brewer_common STATIC
    Config.cc
    Logging.cc
)

target_link_libraries(brewer_common
    ${BOOST_LIBS}
)

add_subdirectory(test)
