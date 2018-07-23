#pragma once

#include <iostream>
#include <dt/node.hpp>
#include <xml.hpp>
#include "test.h"

class TestXml
{
public:
    STest(test_load_fat_xml);
    STest(test_load_small_xml);
    STest(test_extract_xml);
    STest(test_create_xml);
};
