# - Try to find PureData
#  Once done this will define
#  PUREDATA_FOUND - System has PureData
#  PUREDATA_INCLUDE_DIRS - The PureData include directories
#  PUREDATA_EXTRA_DIR - The libraries for PureData extensions

find_path(PUREDATA_INCLUDE_DIR m_pd.h
          HINTS
          /usr/include
          /Applications/Pd-extended.app/Contents/Resources/include)

set(PUREDATA_INCLUDE_DIRS ${PUREDATA_INCLUDE_DIR})

find_path(PUREDATA_EXTRA_DIR Gem
    HINTS
    /usr/lib/pd
    ${PUREDATA_INCLUDE_DIR}/../lib/extra
    /Applications/Pd-extended.app/Contents/Resources/extra
)

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set PUREDATA_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PureData  DEFAULT_MSG
                                  PUREDATA_INCLUDE_DIR)

mark_as_advanced(PUREDATA_INCLUDE_DIR)
