#include "TestXml.hpp"

CXXTest(TestXml, test_extract_xml)
{
    Dp::Dt::Node head = Dp::Xml::LoadFromFile("../xml/test.xml");
    assert_false(head == Dp::Dt::Node::null);
    std::string expected = "<?xml version=\"1.7\" encoding=\"UTF-8\"?>\n<taikai>\n<array id=\"1\" category=\"Kodachi&amp;\" for=\"8\">\n<configuration>\n<goldenscore>\ntrue\n</goldenscore>\n<minute>\n2\n</minute>\n<types>\nIppon\n</types>\n</configuration>\n<configuration for=\"2\">\n<goldenscore>\ntrue\n</goldenscore>\n<minute>\n5\n</minute>\n<types>\nIppon\n</types>\n</configuration>\n</array>\n</taikai>\n";
    assert_true(Dp::Xml::Str(head, 0) == expected);
}

CXXTest(TestXml, test_error_xml)
{
    Dp::Dt::Node head = Dp::Xml::LoadFromFile("../xml/worst.xml");
    assert_true(head != Dp::Dt::Node::null);
    head = Dp::Xml::LoadFromFile("../xml/unknown_file.xml");
    assert_true(head == Dp::Dt::Node::null);
    std::cout << "Unknown file not found" << std::endl;
    Dp::Xml::Write(head, std::cout);
    assert_true(head == Dp::Dt::Node::null);
    head = Dp::Xml::LoadFromFile("../xml/error2.xml");
    assert_true(head == Dp::Dt::Node::null);
    head = Dp::Xml::LoadFromFile("../xml/error3.xml");
    assert_true(head == Dp::Dt::Node::null);
    head = Dp::Xml::LoadFromFile("../xml/error4.xml");
    assert_true(head == Dp::Dt::Node::null);
}

CXXTest(TestXml, test_create_xml)
{
    Dp::Dt::Node head = Dp::Xml::Create("head");
    Dp::Xml::AddAttribute(head, "test", Dp::Dt::data(12));
    head.Add("testeuh.test", Dp::Dt::data(12));
    head.Add("testeuh.block.test", Dp::Dt::data(12));
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<head test=\"12\">\n<testeuh>\n<test>\n12\n</test>\n<block>\n<test>\n12\n</test>\n</block>\n</testeuh>\n</head>\n";
    //<?xml version="1.0" encoding="UTF-8"?>
    //<head test="12">
    //  <testeuh>
    //    <test>
    //      12
    //    </test>
    //    <block>
    //      <test>
    //        12
    //      </test>
    //    </block>
    //  </testeuh>
    //</head>
    assert_true(Dp::Xml::Str(head, 0) == expected);
}