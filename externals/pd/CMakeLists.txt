find_package(PureData REQUIRED)

include_directories(${PUREDATA_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})
add_definitions(-fvisibility=default)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phon2spl-help.pd
               ${CMAKE_CURRENT_BINARY_DIR}/phon2spl-help.pd)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/spl2phon-help.pd
               ${CMAKE_CURRENT_BINARY_DIR}/spl2phon-help.pd)

set(PUREDATA_EXT_INSTALL_DIR "")

if(APPLE)
    set(PUREDATA_EXT_INSTALL_DIR "~/Library/Pd/iso226")

    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".pd_darwin")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined suppress -flat_namespace")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PUREDATA_EXT_INSTALL_DIR ${PUREDATA_EXTRA_DIR})

    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".pd_linux")
endif()

set(CMAKE_INSTALL_NAME_DIR @executable_path)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

add_library(pd_phon2spl SHARED phon2spl.c)
target_link_libraries(pd_phon2spl iso226)

add_library(pd_spl2phon SHARED spl2phon.c)
target_link_libraries(pd_spl2phon iso226)

set_target_properties(pd_phon2spl
    PROPERTIES OUTPUT_NAME phon2spl)
set_target_properties(pd_spl2phon
    PROPERTIES OUTPUT_NAME spl2phon)

# install
if(APPLE)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/phon2spl-help.pd
            DESTINATION ${PUREDATA_EXT_INSTALL_DIR})
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/spl2phon-help.pd
            DESTINATION ${PUREDATA_EXT_INSTALL_DIR})

    install(TARGETS pd_phon2spl
            LIBRARY DESTINATION lib/pd-externals)
    install(TARGETS pd_phon2spl
            LIBRARY DESTINATION ${PUREDATA_EXT_INSTALL_DIR})
    install(TARGETS pd_spl2phon
            LIBRARY DESTINATION lib/pd-externals)
    install(TARGETS pd_spl2phon
            LIBRARY DESTINATION ${PUREDATA_EXT_INSTALL_DIR})
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS pd_phon2spl pd_spl2phon
        LIBRARY DESTINATION lib/pd/extra/iso226
    )
endif()
