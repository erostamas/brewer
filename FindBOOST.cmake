# FIXME - make more flexible with pkg-config

include(FindPackageHandleStandardArgs)

find_path(BOOST_INCLUDE_DIRS
  NAMES boost/bind.hpp
  HINTS ${PREFIX}/usr ${PREFIX}/usr/local
  PATH_SUFFIXES include
)

find_library(BOOST_LIBRARIES
  NAMES boost_unit_test_framework
  HINTS ${PREFIX}/usr ${PREFIX}/usr/local
  PATH_SUFFIXES lib lib64
)

find_package_handle_standard_args(BOOST DEFAULT_MSG BOOST_LIBRARIES BOOST_INCLUDE_DIRS)
