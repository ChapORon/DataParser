include_directories(test/include)

add_definitions(-DTEST=1)

set(TEST ${NAME}Test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(TEST_SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/test/src)
set(TEST_INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/test/include)

set(SOURCES_FILES_TEST
        ${TEST_INCPATH}/test.h
        ${TEST_INCPATH}/TestJson.hpp
        ${TEST_INCPATH}/TestNode.hpp
        ${TEST_INCPATH}/TestSrpt.hpp
        ${TEST_INCPATH}/TestXml.hpp
        ${TEST_SRCPATH}/test.c
        ${TEST_SRCPATH}/TestJson.cpp
        ${TEST_SRCPATH}/TestNode.cpp
        ${TEST_SRCPATH}/TestSrpt.cpp
        ${TEST_SRCPATH}/TestXml.cpp
        ${TEST_SRCPATH}/main.cpp)

add_executable(${NAME}Test ${SOURCE_FILES} ${SOURCES_FILES_TEST})