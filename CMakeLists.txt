cmake_minimum_required(VERSION 3.8)
project(DataParser)

set(CMAKE_CXX_STANDARD 14)

set(NAME DataParser)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

if (CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Test)
    set(NAME ${NAME}D)
    add_definitions(-DDEBUG=1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast -g3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")
endif()

set(SOURCE_FILES
        ${INCPATH}/dt/data.hpp
        ${INCPATH}/dt/node.hpp
        ${INCPATH}/json.hpp
        ${INCPATH}/parser.hpp
        ${INCPATH}/sppt.hpp
        ${INCPATH}/xml.hpp
        ${SRCPATH}/dt/data.cpp
        ${SRCPATH}/dt/node.cpp
        ${SRCPATH}/json.cpp
        ${SRCPATH}/parser.cpp
        ${SRCPATH}/sppt.cpp
        ${SRCPATH}/xml.cpp)

add_library(${NAME} SHARED ${SOURCE_FILES})
if (CMAKE_BUILD_TYPE MATCHES Test)
    include(test/UnitTest.cmake)
endif()