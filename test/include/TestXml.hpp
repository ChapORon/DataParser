#pragma once

#include <iostream>
#include <dt/node.hpp>
#include <xml.hpp>
#include "test.h"

class TestXml
{
public:
    static Test(test_load_xml);
    static Test(test_create_xml);
    static Test(test_get_xml);
};
