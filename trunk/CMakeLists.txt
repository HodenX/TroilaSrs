cmake_minimum_required(VERSION 3.10)

project(SRS)

set(CMAKE_C_COMPILE "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations -Wno-deprecated-declarations")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g3 -ggdb")  
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

if(NOT RSR_CONFIGURED)
execute_process(
    COMMAND ./configure --without-utest --with-ingest  --jobs=22
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE RESULT_VAR 
    ERROR_VARIABLE ERROR_MSG
)
if(NOT RESULT_VAR EQUAL 0)
        message(FATAL_ERROR "build SRS failed,${ERROR_MSG}")
    endif()

    set(RSR_CONFIGURED true CACHE BOOL "")
endif() # PTLIB_NEED_CONFIGURE



add_custom_target(srs_debug 
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
