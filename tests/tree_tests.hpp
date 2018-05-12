#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "../tree.hpp"

class aTreeTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(aTreeTest);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testInsert2);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testEmptiness);
    CPPUNIT_TEST(testConstIterator);
    CPPUNIT_TEST(testDeletion);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testCopyAssignment);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testInsert();
    void testInsert2();
    void testSize();
    void testConstIterator();
    void testCopyConstructor();
    void testCopyAssignment();
    void testDeletion();
    void testEquality();
    void testEmptiness();
private:
    ms::tree<int>* tree;
    ms::tree<int>* s_tree;
};
