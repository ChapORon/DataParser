#include "BenchXml.hpp"

CXXTest(BenchXml, boost_load_fat_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./fat.xml", tree);
}

CXXTest(BenchXml, test_load_fat_xml)
{
    dp::dt::node head = dp::xml::loadFromFile("./fat.xml");
}

CXXTest(BenchXml, boost_load_small_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./test.xml", tree);
}

CXXTest(BenchXml, test_load_small_xml)
{
    dp::dt::node head = dp::xml::loadFromFile("./test.xml");
}