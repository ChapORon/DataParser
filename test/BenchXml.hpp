#pragma once

#include <iostream>
#include <Dp/Dt/Node.hpp>
#include <Dp/Xml.hpp>
#include "test.h"

class BenchXml
{
public:
    STest(test_load_fat_xml);
    STest(test_load_small_xml);
    STest(test_write_fat_xml);
    STest(test_write_small_xml);
};
