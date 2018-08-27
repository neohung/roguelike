cmake_minimum_required(VERSION 2.8)
project("test")

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


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-rpath=/usr/local/lib")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath=/usr/local/lib")

find_package(ZLIB REQUIRED)
find_package (Boost REQUIRED COMPONENTS serialization system)
#find_package (Boost 1.54.0 REQUIRED COMPONENTS system filesystem)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
#find_package(fakemodule REQUIRED)

add_library(testapi 	testlib/src/testapi.cpp)

target_include_directories(testapi PUBLIC
		"$<BUILD_INTERFACE:${ZLIB_INCLUDE_DIRS}>" 
                "$<BUILD_INTERFACE:${SFML_INCLUDE_DIR}>"
		)

target_link_libraries(testapi PUBLIC 
                ${ZLIB_LIBRARIES}
                ${SFML_LIBRARIES}
                )

if(NOT MSVC)
  target_compile_options(testapi PUBLIC -O3 -Wall -Wpedantic -march=native -mtune=native -g)
else()
  target_compile_options(testapi PUBLIC /W3 /EHsc)
endif()

install (TARGETS testapi
         ARCHIVE DESTINATION ~/temp/test/lib
         LIBRARY DESTINATION ~/temp/test/lib
         RUNTIME DESTINATION ~/temp/test/bin)

set(TEST_HEADERS
     testlib/inc/testapi.h
   )

#Copy header 
install(FILES ${TEST_HEADERS}
        #DESTINATION "include/testapi"
        DESTINATION "~/temp/test/include/testapi"
       )
MESSAGE(STATUS "${Green} ${SFML_LIBRARIES} ${CleanColor}")
MESSAGE(STATUS "${Green} ${Boost_LIBRARIES} ${CleanColor}")
add_executable(ex1 examples/ex1.cpp)
include_directories( ${Boost_INCLUDE_DIR})
target_link_libraries(ex1 
                      testapi 
                      ${Boost_LIBRARIES}
                     )
