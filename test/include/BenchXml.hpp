#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <dt/node.hpp>
#include <xml.hpp>
#include "test.h"

class BenchXml
{
public:
    STest(boost_load_fat_xml);
    STest(test_load_fat_xml);
    STest(boost_load_small_xml);
    STest(test_load_small_xml);
    STest(boost_write_fat_xml);
    STest(test_write_fat_xml);
    STest(boost_write_small_xml);
    STest(test_write_small_xml);
};
