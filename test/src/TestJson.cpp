#include "TestJson.hpp"

CXXTest(TestJson, test_extract_json)
{

}

CXXTest(TestJson, test_create_json)
{
    std::vector<int> array = {1, 2, 3};
    dp::dt::node head("head");
    head.add("test", dp::dt::data(true));
    head.add("block.test", dp::dt::data(12));
    dp::json::addArray(head, "array", array);
    dp::json::addToArray(head, "array", "4");
    std::string expected = "{\n\"head\": {\n\"test\": true,\n\"block\": {\n\"test\": 12\n},\n\"array\": [\n1,\n2,\n3,\n4\n]\n}\n}\n";
    //{
    //  "head": {
    //    "test": true,
    //    "block": {
    //      "test": 12
    //    },
    //    "array": [
    //      1,
    //      2,
    //      3,
    //      4
    //    ]
    //  }
    //}
    assert_true(dp::json::str(head, 0) == expected);
}