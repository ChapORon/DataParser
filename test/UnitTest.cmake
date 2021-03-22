include_directories(test/include)

add_definitions(-DTEST=1)

set(TEST ${NAME}Test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/bin)

set(SOURCES_FILES_TEST
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/test/BenchXml.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJson.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNode.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestXml.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/test/BenchXml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestJson.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/TestXml.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)

add_executable(${NAME}Test ${SOURCE_FILES} ${SOURCES_FILES_TEST})