#include "TestJson.hpp"

CXXTest(TestJson, test_extract_json)
{

}

CXXTest(TestJson, test_create_json)
{
    std::vector<std::string> array = {"1", "2", "3"};
    dp::dt::node head(std::string("head"));
    head.add("test", dp::dt::data("12"));
    head.add("block.test", dp::dt::data("12"));
    dp::json::addArray(head, "array", array);
    dp::json::addToArray(head, "array", "4");
    dp::json::write(head, std::cout);
    //std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<head test=\"12\">\n<testeuh>\n<test>\n12\n</test>\n<block>\n<test>\n12\n</test>\n</block>\n</testeuh>\n</head>\n";
    //assert_true(dp::xml::str(head, 0) == expected);
}