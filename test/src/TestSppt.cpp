#include "TestSppt.hpp"

CXXTest(TestSppt, test_extract_sppt)
{

}

CXXTest(TestSppt, test_create_sppt)
{
    std::vector<int> array = {1, 2, 3};
    dp::dt::node head("head");
    head.add("test", dp::dt::data(true));
    head.add("block.test", dp::dt::data(12));
    head.add("block.test.innerBlockFloat", dp::dt::data(12.3));
    head.add("block.test.innerBlockString", dp::dt::data("String"));
    dp::sppt::write(head, std::cout);
//    std::string expected = "\"head\": {\n\"test\": true,\n\"block\": {\n\"test\": 12\n},\n\"array\": [\n1,\n2,\n3,\n4\n]\n}\n";
//    assert_true(dp::sppt::str(head, 0) == expected);
}