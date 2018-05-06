#include "tree_tests.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(aTreeTest);

using namespace ms;

void aTreeTest::setUp() {

}

void aTreeTest::tearDown() {

}

void aTreeTest::testInsert() {
    aTree<int> tree{};
    CPPUNIT_ASSERT(tree.get_root_node() == nullptr);
    CPPUNIT_ASSERT(tree.add_root(3));
    CPPUNIT_ASSERT(tree.get_root_node()->get_parent_node() == nullptr);
    CPPUNIT_ASSERT(tree.get_root_node() != nullptr);
    CPPUNIT_ASSERT_EQUAL(3, tree.get_root_node()->get_value());
    CPPUNIT_ASSERT(tree.get_root_node()->get_children().size() == 0);
    CPPUNIT_ASSERT(!tree.add_root(4));
    CPPUNIT_ASSERT_EQUAL(3, tree.get_root_node()->get_value());
    CPPUNIT_ASSERT(tree.get_root_node()->get_children().size() == 0);
}

void aTreeTest::testConstIterator() {
    aTree<int> tree{};
    CPPUNIT_ASSERT(tree.add_root(3));
    tree.get_root_node()->insert_child(4);
    tree.get_root_node()->insert_child(5);
    tree.get_root_node()->insert_child(6);
    tree.get_root_node()->get_children()[0]->insert_child(7);

    auto iterator = tree.begin();
    CPPUNIT_ASSERT(iterator != tree.end());
    CPPUNIT_ASSERT((iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(3, *iterator);
    iterator++;
    CPPUNIT_ASSERT(iterator != tree.end());
    CPPUNIT_ASSERT((iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(4, *iterator);
    
    auto second_iterator{iterator};
    
    ++iterator;
    CPPUNIT_ASSERT(iterator != tree.end());
    CPPUNIT_ASSERT((iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(7, *iterator);
    ++iterator;
    CPPUNIT_ASSERT(iterator != tree.end());
    CPPUNIT_ASSERT((iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(5, *iterator);
    iterator++;
    CPPUNIT_ASSERT(iterator != tree.end());
    CPPUNIT_ASSERT((iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(6, *iterator);
    
    CPPUNIT_ASSERT(second_iterator != tree.end());
    CPPUNIT_ASSERT((second_iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(4, *second_iterator);
    
    ++iterator;
    CPPUNIT_ASSERT((iterator != tree.end()) == false);
    CPPUNIT_ASSERT(iterator == tree.end());
    
    CPPUNIT_ASSERT(second_iterator != tree.end());
    CPPUNIT_ASSERT((second_iterator == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(4, *second_iterator);
    
    CPPUNIT_ASSERT(second_iterator+2 != tree.end());
    CPPUNIT_ASSERT((second_iterator+2 == tree.end()) == false);
    CPPUNIT_ASSERT_EQUAL(5, *(second_iterator+2));
    
}

void aTreeTest::testEmptiness() {
    aTree<int> tree{};
    CPPUNIT_ASSERT(tree.is_empty());
    CPPUNIT_ASSERT(tree.get_root_node() == nullptr);
    CPPUNIT_ASSERT(tree.add_root(3));
    CPPUNIT_ASSERT(!tree.is_empty());
    tree.clear();
    CPPUNIT_ASSERT(tree.is_empty());
    CPPUNIT_ASSERT(tree.get_root_node() == nullptr);
    CPPUNIT_ASSERT(tree.add_root(3));
    CPPUNIT_ASSERT(!tree.add_root(4));
    tree.get_root_node()->insert_child(4);
    tree.get_root_node()->insert_child(5);
    tree.get_root_node()->insert_child(6);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[0]->get_parent_node() == tree.get_root_node());
    tree.get_root_node()->get_children()[0]->remove();
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[0]->get_parent_node() == tree.get_root_node());
    tree.get_root_node()->get_children()[0]->remove();
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[0]->get_parent_node() == tree.get_root_node());
    tree.get_root_node()->get_children()[0]->remove();
    CPPUNIT_ASSERT(tree.get_root_node()->get_parent_node() == nullptr);
    CPPUNIT_ASSERT(!tree.is_empty());
    tree.get_root_node()->remove();
    CPPUNIT_ASSERT(tree.is_empty());
}
