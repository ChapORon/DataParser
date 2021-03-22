cmake_minimum_required(VERSION 3.8)
project(DataParser)

set(CMAKE_CXX_STANDARD 17)

set(NAME DataParser)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(.)

if (CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Test)
#    set(NAME ${NAME}D)
    add_definitions(-DDEBUG=1)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast -g3")
#else()
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")
endif()

set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Dt/Data.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Dt/Data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Dt/Node.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Dt/Node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Json.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Json.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Parser.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Xml.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Parser/Xml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Json.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Json.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/StringUtils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/StringUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Xml.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Dp/Xml.cpp)

add_library(${NAME} SHARED ${SOURCE_FILES})
add_library(${NAME}-s STATIC ${SOURCE_FILES})
if (CMAKE_BUILD_TYPE MATCHES Test)
    include(test/UnitTest.cmake)
endif()