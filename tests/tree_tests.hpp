#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "../aTree.hpp"

class aTreeTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(aTreeTest);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testEmptiness);
    CPPUNIT_TEST(testConstIterator);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testInsert();
    void testConstIterator();
    void testEmptiness();
};
