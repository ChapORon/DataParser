#include "TestXml.hpp"

CXXTest(TestXml, test_extract_xml)
{
    dp::dt::node head = dp::xml::loadFromFile("./test.xml");
    assert_false(head == dp::dt::node::null);
    std::string expected = "<?xml version=\"1.7\" encoding=\"UTF-8\"?>\n<taikai>\n<array id=\"1\" category=\"Kodachi&amp;\" for=\"8\">\n<configuration>\n<goldenscore>\ntrue\n</goldenscore>\n<minute>\n2\n</minute>\n<types>\nIppon\n</types>\n</configuration>\n<configuration for=\"2\">\n<goldenscore>\ntrue\n</goldenscore>\n<minute>\n5\n</minute>\n<types>\nIppon\n</types>\n</configuration>\n</array>\n</taikai>\n";
    assert_true(dp::xml::str(head, 0) == expected);
}

CXXTest(TestXml, test_error_xml)
{
    dp::dt::node head = dp::xml::loadFromFile("./worst.xml");
    assert_true(head != dp::dt::node::null);
    head = dp::xml::loadFromFile("./unknown_file.xml");
    assert_true(head == dp::dt::node::null);
    std::cout << "Unknown file not found" << std::endl;
    dp::xml::write(head, std::cout);
    assert_true(head == dp::dt::node::null);
    head = dp::xml::loadFromFile("./error2.xml");
    assert_true(head == dp::dt::node::null);
    head = dp::xml::loadFromFile("./error3.xml");
    assert_true(head == dp::dt::node::null);
    head = dp::xml::loadFromFile("./error4.xml");
    assert_true(head == dp::dt::node::null);
}

CXXTest(TestXml, test_create_xml)
{
    dp::dt::node head = dp::xml::create("head");
    dp::xml::addAttribute(head, "test", dp::dt::data(12));
    head.add("testeuh.test", dp::dt::data(12));
    head.add("testeuh.block.test", dp::dt::data(12));
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
    assert_true(dp::xml::str(head, 0) == expected);
}