#include "TestJson.hpp"

CXXTest(TestJson, test_extract_json)
{

}

CXXTest(TestJson, test_create_json)
{
    std::vector<int> array = {1, 2, 3};
    Dp::Dt::Node head("head");
    head.Add("test", Dp::Dt::data(true));
    head.Add("block.test", Dp::Dt::data(12));
    Dp::Json::AddArray(head, "array", array);
    Dp::Json::AddToArray(head, "array", "4");
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
    assert_true(Dp::Json::Str(head, 0) == expected);
}