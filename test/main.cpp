#include "BenchXml.hpp"
#include "TestJson.hpp"
#include "TestNode.hpp"
#include "TestXml.hpp"

static void register_unit_test()
{
    test_register("test_add_node", &TestNode::test_add_node);
    test_register("test_del_node", &TestNode::test_del_node);
    test_register("test_get_node", &TestNode::test_get_node);
    //test_register("test_extract_json", &TestJson::test_extract_json);
    test_register("test_create_json", &TestJson::test_create_json);
    test_register("test_extract_xml", &TestXml::test_extract_xml);
    test_register("test_error_xml", &TestXml::test_error_xml);
    test_register("test_create_xml", &TestXml::test_create_xml);
}

static void register_benchmark()
{
    timer_register("dp load small xml", &BenchXml::test_load_small_xml);
    timer_register("dp load fat xml", &BenchXml::test_load_fat_xml);
    timer_register("dp write small xml", &BenchXml::test_write_small_xml);
    timer_register("dp write fat xml", &BenchXml::test_write_fat_xml);
}

int main(int ac, char **av)
{
    register_unit_test();
    register_benchmark();
    return run_test(ac, av);
}