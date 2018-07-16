#include "TestNode.hpp"

CXXTest(TestNode, test_add_node)
{
    dp::dt::node head("head");
    head.add("test.value", dp::dt::data(1));
    head.add("test.value", dp::dt::data(2));
    head.add("test.value", dp::dt::data(3));
    std::string expected = "head\n\ttest\n\t\t\"value\":1\n\t\t\"value\":2\n\t\t\"value\":3\n";
    assert_true(dp::mew::str(head) == expected);
}

CXXTest(TestNode, test_get_node)
{
    dp::dt::node head("head");
    head.add("testeuh.test.path.invalid", dp::dt::data(1));
    head.add("testeuh.test(2).path.valid", dp::dt::data(2));
    head.add("testeuh.test(3).path.invalid", dp::dt::data(3));
    assert_true(head.get("testeuh.test.path.valid").value().getInt() == 2);
    assert_true(head.get("testeuh.test(1).path.valid") == dp::dt::node::null);
}

CXXTest(TestNode, test_del_node)
{
    dp::dt::node head("head");
    head.add("test.value", dp::dt::data(1));
    head.add("test.value", dp::dt::data(2));
    head.add("test.value", dp::dt::data(3));
    head.remove("test.value(3)");
    std::string expected = "head\n\ttest\n\t\t\"value\":1\n\t\t\"value\":2\n";
    assert_true(dp::mew::str(head) == expected);
    head.remove("test.value");
    expected = "head\n\ttest\n\t\t\"value\":2\n";
    assert_true(dp::mew::str(head) == expected);
}