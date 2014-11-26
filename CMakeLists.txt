project(iso226)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_PATH "cmake")

# build universal binaries
set(CMAKE_OSX_ARCHITECTURES x86_64;i386)
add_definitions(-fvisibility=hidden)
add_definitions(-Wall)


add_library(iso226 STATIC iso226.c)

add_executable(phon2spl phon2spl.c)
target_link_libraries(phon2spl iso226)

add_subdirectory(externals)

# install target
install(TARGETS iso226 phon2spl
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib)

# uninstall target
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# package
set(CPACK_PACKAGE_VENDOR "sp")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_GENERATOR TBZ2)
set(CPACK_SOURCE_GENERATOR "TBZ2")

set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
    "~$"
    "^${PROJECT_SOURCE_DIR}.*/\\\\.git/"
    "^.*/*.user$"
)

include(CPack)
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
