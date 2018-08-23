
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(CleanColor "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# $ENV{HOME} can read variable, $ENV{CMAKE_SOURCE_DIR} / $ENV{CMAKE_BINARY_DIR}
# TEST_INCLUDE_DIRS-NOTFOUND
# Would search testapi.h 
find_path(TEST_INCLUDE_DIRS testapii
          HINTS "/usr/local/include" $ENV{HOME}/temp/test/include)

#set(TEST_INCLUDE_DIRS ${TEST_INCLUDE_DIRS})
#include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(testapi DEFAULT_MSG TEST_INCLUDE_DIRS)
#mark_as_advanced(TEST_INCLUDE_DIRS)

if (TESTAPI_FOUND)
  MESSAGE(STATUS "${Green} Found testapi.h in ${TEST_INCLUDE_DIRS} ${CleanColor}")
else(TESTAPI_FOUND)
  #MESSAGE(WARNING "${Yellow}WARING: testapi.h not found ${CleanColor}")
  MESSAGE(FATAL_ERROR "${BoldRed}FATAL_ERROR: TEST FAKE MODULE${CleanColor}")
endif(TESTAPI_FOUND)
