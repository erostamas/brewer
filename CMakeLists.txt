# compiler and linker flags
if ((NOT CMAKE_CXX_FLAGS) OR (CMAKE_CXX_FLAGS MATCHES "^[ \t]*$"))
  set(CXX11_FLAG "-std=c++11")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.2")
      set(CXX11_FLAG "-std=c++0x")
  endif()
  set(CMAKE_CXX_FLAGS "-O3 -g ${CXX11_FLAG} -Werror -Wall -DNDEBUG -lpthread")
  if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -fprofile-arcs -ftest-coverage")
  endif()
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall")
  endif()
endif()

add_executable(brewer
main.cc
TcpInterface.cc
ProcessControl.cc)