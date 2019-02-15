cmake_minimum_required(VERSION 3.8)
project(DataParser)

set(CMAKE_CXX_STANDARD 17)

set(NAME DataParser)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(include)

if (CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Test)
    set(NAME ${NAME}D)
    add_definitions(-DDEBUG=1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast -g3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")
endif()

set(SOURCE_FILES
        ${INCPATH}/dp/dt/data.hpp
        ${INCPATH}/dp/dt/node.hpp
        ${INCPATH}/dp/parser/json.hpp
        ${INCPATH}/dp/parser/parser.hpp
        ${INCPATH}/dp/parser/srpt.hpp
        ${INCPATH}/dp/parser/xml.hpp
        ${INCPATH}/dp/json.hpp
        ${INCPATH}/dp/srpt.hpp
        ${INCPATH}/dp/xml.hpp
        ${SRCPATH}/dp/dt/data.cpp
        ${SRCPATH}/dp/dt/node.cpp
        ${SRCPATH}/dp/parser/json.cpp
        ${SRCPATH}/dp/parser/parser.cpp
        ${SRCPATH}/dp/parser/srpt.cpp
        ${SRCPATH}/dp/parser/xml.cpp
        ${SRCPATH}/dp/json.cpp
        ${SRCPATH}/dp/srpt.cpp
        ${SRCPATH}/dp/xml.cpp)

add_library(${NAME} SHARED ${SOURCE_FILES})
if (CMAKE_BUILD_TYPE MATCHES Test)
    include(test/UnitTest.cmake)
endif()