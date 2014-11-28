include(FindPureData)
include_directories(PD_INCLUDE_DIR)
include_directories(${CMAKE_SOURCE_DIR})
add_definitions(-fvisibility=default)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phon2spl-help.pd
               ${CMAKE_CURRENT_BINARY_DIR}/phon2spl-help.pd)

if(APPLE)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".pd_darwin")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined suppress -flat_namespace")

    # install paths
    set(PD_EXT_INSTALL_DIR "~/Library/Pd/iso226")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/phon2spl-help.pd
            DESTINATION ${PD_EXT_INSTALL_DIR})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/phon2spl.pd_darwin
            DESTINATION ${PD_EXT_INSTALL_DIR})
endif()

add_library(pd_phon2spl SHARED phon2spl.c)
target_link_libraries(pd_phon2spl iso226)

set_target_properties(pd_phon2spl
    PROPERTIES OUTPUT_NAME phon2spl)
