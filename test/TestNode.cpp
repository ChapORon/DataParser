#include "TestNode.hpp"

CXXTest(TestNode, test_add_node)
{
    Dp::Dt::Node head("head");
    head.Add("test.value", Dp::Dt::Data(1));
    head.Add("test.value", Dp::Dt::Data(2));
    head.Add("test.value", Dp::Dt::Data(3));
    std::string expected = "{\"head\":{\"test\":{\"value\":[1,2,3]}}}";
    assert_true(Dp::Json::Str(head, 0, 0, false) == expected);
}

CXXTest(TestNode, test_get_node)
{
    Dp::Dt::Node head("head");
    head.Add("testeuh.test.path.invalid", Dp::Dt::Data(1));
    head.Add("testeuh.test(2).path.valid", Dp::Dt::Data(2));
    head.Add("testeuh.test(3).path.invalid", Dp::Dt::Data(3));
    assert_true(head.Get<int>("testeuh.test.path.valid") == 2);
    assert_true(head.GetNode("testeuh.test(1).path.valid") == Dp::Dt::Node::null);
}

CXXTest(TestNode, test_del_node)
{
    Dp::Dt::Node head("head");
    head.Add("test.value", Dp::Dt::Data(1));
    head.Add("test.value", Dp::Dt::Data(2));
    head.Add("test.value", Dp::Dt::Data(3));
	head.Remove("test.value(3)");
	std::string expected = "{\"head\":{\"test\":{\"value\":[1,2]}}}";
    assert_true(Dp::Json::Str(head, 0, 0, false) == expected);
    head.Remove("test.value");
	expected = "{\"head\":{\"test\":{\"value\":[2]}}}";
    assert_true(Dp::Json::Str(head, 0, 0, false) == expected);
}