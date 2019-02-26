#include "TestNode.hpp"

CXXTest(TestNode, test_add_node)
{
    dp::dt::node head("head");
    head.add("test.value", dp::dt::data(1));
    head.add("test.value", dp::dt::data(2));
    head.add("test.value", dp::dt::data(3));
    std::string expected = "head\n\ttest\n2\t\"value\":1\n2\t\"value\":2\n2\t\"value\":3\n";
    assert_true(dp::srpt::str(head) == expected);
}

CXXTest(TestNode, test_get_node)
{
    dp::dt::node head("head");
    head.add("testeuh.test.path.invalid", dp::dt::data(1));
    head.add("testeuh.test(2).path.valid", dp::dt::data(2));
    head.add("testeuh.test(3).path.invalid", dp::dt::data(3));
    assert_true(head.get<int>("testeuh.test.path.valid") == 2);
    assert_true(head.getNode("testeuh.test(1).path.valid") == dp::dt::node::null);
}

CXXTest(TestNode, test_del_node)
{
    dp::dt::node head("head");
    head.add("test.value", dp::dt::data(1));
    head.add("test.value", dp::dt::data(2));
    head.add("test.value", dp::dt::data(3));
    head.remove("test.value(3)");
    std::string expected = "head\n\ttest\n2\t\"value\":1\n2\t\"value\":2\n";
    assert_true(dp::srpt::str(head) == expected);
    head.remove("test.value");
    expected = "head\n\ttest\n2\t\"value\":2\n";
    assert_true(dp::srpt::str(head) == expected);
}