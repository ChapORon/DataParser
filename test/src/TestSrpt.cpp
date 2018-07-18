#include "TestSrpt.hpp"

CXXTest(TestSrpt, test_extract_srpt)
{

}

CXXTest(TestSrpt, test_create_srpt)
{
    std::vector<int> array = {1, 2, 3};
    dp::dt::node head("head");
    head.add("test", dp::dt::data(true));
    head.add("char", dp::dt::data('m'));
    head.add("block.test", dp::dt::data(12));
    head.add("block.test.innerBlockFloat", dp::dt::data("12.3"));
    head.add("block.test.innerBlockString", dp::dt::data("String"));
    std::string expected = "head\n\t\"test\":tr\n\t\"char\":m\n\tblock\n2\t\"test\":12\n3\t\"innerBlockFloat\":12.3\n3\t\"innerBlockString\":\"String\"\n";
    //head
    //        "test":tr
    //        "char":m
    //        block
    //2       "test":12
    //3       "innerBlockFloat":12.3
    //3       "innerBlockString":"String"
    assert_true(dp::srpt::str(head) == expected);
}