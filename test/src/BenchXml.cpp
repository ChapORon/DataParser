#include "BenchXml.hpp"

CXXTest(BenchXml, boost_load_fat_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./fat.xml", tree);
}

CXXTest(BenchXml, test_load_fat_xml)
{
    dp::dt::node tree = dp::xml::loadFromFile("./fat.xml");
}

CXXTest(BenchXml, boost_load_small_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./test.xml", tree);
}

CXXTest(BenchXml, test_load_small_xml)
{
    dp::dt::node tree = dp::xml::loadFromFile("./test.xml");
}

CXXTest(BenchXml, boost_write_fat_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./fat.xml", tree);
    boost::property_tree::write_xml("boost_fat.xml", tree);
}

CXXTest(BenchXml, test_write_fat_xml)
{
    dp::dt::node tree = dp::xml::loadFromFile("./fat.xml");
    dp::xml::write(tree, "dp_fat.xml");
}

CXXTest(BenchXml, boost_write_small_xml)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml("./test.xml", tree);
    boost::property_tree::write_xml("boost_small.xml", tree);
}

CXXTest(BenchXml, test_write_small_xml)
{
    dp::dt::node tree = dp::xml::loadFromFile("./test.xml");
    dp::xml::write(tree, "dp_small.xml");
}