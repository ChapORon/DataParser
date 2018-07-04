cmake_minimum_required(VERSION 3.8)
project(DataParser)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(test)

set(NAME DataParser)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(NAME ${NAME}D)
    add_definitions(-DDEBUG=1)
endif()

set(SOURCE_FILES
        ${INCPATH}/dt/data.hpp
        ${INCPATH}/dt/node.hpp
        ${INCPATH}/dt/root.hpp
        ${INCPATH}/XML/File.hpp
        ${INCPATH}/XML/Markup.hpp
        ${INCPATH}/XML/Object.hpp
        ${SRCPATH}/dt/data.cpp
        ${SRCPATH}/dt/node.cpp
        ${SRCPATH}/dt/root.cpp
        ${SRCPATH}/XML/File.cpp
        ${SRCPATH}/XML/Markup.cpp
        ${SRCPATH}/XML/InnerMarkup.cpp)

add_library(${NAME} SHARED ${SOURCE_FILES})
