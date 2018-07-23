#include "BenchXml.hpp"
#include "TestJson.hpp"
#include "TestNode.hpp"
#include "TestSrpt.hpp"
#include "TestXml.hpp"

int main(int ac, char **av)
{
    //test_register("test_extract_sppt", &TestSrpt::test_extract_srpt);
    test_register("test_create_sppt", &TestSrpt::test_create_srpt);
    test_register("test_add_node", &TestNode::test_add_node);
    test_register("test_del_node", &TestNode::test_del_node);
    test_register("test_get_node", &TestNode::test_get_node);
    //test_register("test_extract_json", &TestJson::test_extract_json);
    test_register("test_create_json", &TestJson::test_create_json);
    test_register("test_extract_xml", &TestXml::test_extract_xml);
    test_register("test_create_xml", &TestXml::test_create_xml);
    timer_register("boost load small xml", &BenchXml::boost_load_small_xml);
    timer_register("dp load small xml", &BenchXml::test_load_small_xml);
    timer_register("boost load fat xml", &BenchXml::boost_load_fat_xml);
    timer_register("dp load fat xml", &BenchXml::test_load_fat_xml);
    return run_test(ac, av);
}