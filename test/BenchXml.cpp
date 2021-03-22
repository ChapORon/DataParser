#include "BenchXml.hpp"

CXXTest(BenchXml, test_load_fat_xml)
{
    Dp::Dt::Node tree = Dp::Xml::LoadFromFile("../xml/fat.xml");
}

CXXTest(BenchXml, test_load_small_xml)
{
    Dp::Dt::Node tree = Dp::Xml::LoadFromFile("../xml/test.xml");
}

CXXTest(BenchXml, test_write_fat_xml)
{
    Dp::Dt::Node tree = Dp::Xml::LoadFromFile("../xml/fat.xml");
    Dp::Xml::Write(tree, "dp_fat.xml");
}

CXXTest(BenchXml, test_write_small_xml)
{
    Dp::Dt::Node tree = Dp::Xml::LoadFromFile("../xml/test.xml");
    Dp::Xml::Write(tree, "dp_small.xml");
}