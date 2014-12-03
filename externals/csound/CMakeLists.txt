find_package(CSound6 REQUIRED)

include_directories(${CSOUND6_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_cs_iso226.csd
               ${CMAKE_CURRENT_BINARY_DIR}/test_cs_iso226.csd)

set(CMAKE_INSTALL_NAME_DIR @executable_path)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
#add_definitions(-DUSE_DOUBLE)
add_library(cs_iso226 SHARED cs_iso226.c)
target_link_libraries(cs_iso226 iso226)

set_target_properties(cs_iso226
    PROPERTIES OUTPUT_NAME iso226)
