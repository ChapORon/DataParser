#include "TestJson.hpp"
#include "TestNode.hpp"
#include "TestXml.hpp"

int main(int ac, char **av)
{
    //test_register("test_extract_json", &TestJson::test_extract_json);
    test_register("test_create_json", &TestJson::test_create_json);
    test_register("test_extract_xml", &TestXml::test_extract_xml);
    test_register("test_create_xml", &TestXml::test_create_xml);
    test_register("test_add_node", &TestNode::test_add_node);
    test_register("test_del_node", &TestNode::test_del_node);
    test_register("test_get_node", &TestNode::test_get_node);
    return run_test(ac, av);
}