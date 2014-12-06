# - Try to find CSound6
# Once done this will define
#  CSOUND6_FOUND - System has CSound
#  CSOUND6_INCLUDE_DIRS - The CSound include directories
#  CSOUND6_LIBRARIES - The libraries needed to use CSound

find_path(CSOUND6_INCLUDE_DIR csdl.h
          HINTS
            /usr/include/csound
            /Library/Frameworks/CsoundLib64.framework/Versions/6.0/Headers/
            /Library/Frameworks/CsoundLib64.framework/Versions/Current/Headers/
			$ENV{PROGRAMFILES}/CSound6/include/csound
          PATH_SUFFIXES csound)


#set(LIBXML2_LIBRARIES ${LIBXML2_LIBRARY} )
set(CSOUND6_INCLUDE_DIRS ${CSOUND6_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CSOUND6_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CSound6  DEFAULT_MSG
                                  CSOUND6_INCLUDE_DIR)

mark_as_advanced(CSOUND6_INCLUDE_DIR CSOUND6_LIBRARY)
