cmake_minimum_required(VERSION 3.1)
project("test")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(ZLIB REQUIRED)
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

#add_executable(ex1 examples/ex1/main.cpp)
#target_link_libraries(ex1 testapi)
