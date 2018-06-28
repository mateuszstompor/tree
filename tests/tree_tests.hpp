#pragma once

#define TESTS

#include <cppunit/extensions/HelperMacros.h>
#include <chrono>
#include <string>
#include <functional>
#include "../tree.hpp"


class aTreeTest : public CppUnit::TestFixture {
    
    
    CPPUNIT_TEST_SUITE(aTreeTest);
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testInsert2);
    CPPUNIT_TEST(testInsert3);
    CPPUNIT_TEST(testInsert4);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testEmptiness);
    CPPUNIT_TEST(testConstIterator);
    CPPUNIT_TEST(testDeletion);
    CPPUNIT_TEST(testParentIterator);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testCopyAssignment);
    CPPUNIT_TEST(testReverseIterator);
    CPPUNIT_TEST(testConstReverseIterator);
    CPPUNIT_TEST(testConversion);
    CPPUNIT_TEST(testInsertTree);
    CPPUNIT_TEST(testLambdaCalls);
    CPPUNIT_TEST(testInsert5);
    CPPUNIT_TEST(testPerformance);
    CPPUNIT_TEST(testTreeConversionConstructor);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testInsert();
    void testInsert2();
    void testInsert3();
    void testInsert4();
    void testInsert5();
    void testSize();
    void testReverseIterator();
    void testConstReverseIterator();
    void testConstIterator();
    void testParentIterator();
    void testCopyConstructor();
    void testCopyAssignment();
    void testDeletion();
    void testEquality();
    void testLambdaCalls();
    void testEmptiness();
    void testConversion();
    void testInsertTree();
    void testPerformance();
    void testTreeConversionConstructor();
private:
    ms::tree<int>* tree;
    ms::tree<int>* s_tree;
    ms::tree<int>  t_tree;
};
