#include "TestJson.hpp"
#include "TestXml.hpp"

int main(int ac, char **av)
{
    //test_register("test_extract_json", &TestJson::test_extract_json);
    test_register("test_create_json", &TestJson::test_create_json);
    test_register("test_load_xml", &TestXml::test_load_xml);
    test_register("test_create_xml", &TestXml::test_create_xml);
    test_register("test_get_xml", &TestXml::test_get_xml);
    return run_test(ac, av);
}