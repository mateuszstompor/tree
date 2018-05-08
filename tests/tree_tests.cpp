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

void aTreeTest::testSize() {
    aTree<int> tree{};
    CPPUNIT_ASSERT(0 == tree.size());
    CPPUNIT_ASSERT(tree.add_root(3));
    CPPUNIT_ASSERT(1 == tree.size());
    tree.get_root_node()->insert_child(4);
    CPPUNIT_ASSERT(2 == tree.size());
    tree.get_root_node()->insert_child(5);
    CPPUNIT_ASSERT(3 == tree.size());
    tree.get_root_node()->insert_child(6);
    CPPUNIT_ASSERT(4 == tree.size());
    tree.clear();
    CPPUNIT_ASSERT(0 == tree.size());
    
    aTree<int> second_tree{};
    CPPUNIT_ASSERT(second_tree.add_root(3));
    second_tree.get_root_node()->insert_child(4);
    CPPUNIT_ASSERT(2 == second_tree.size());
    second_tree.get_root_node()->get_children()[0]->remove();
    CPPUNIT_ASSERT(1 == second_tree.size());
    second_tree.get_root_node()->insert_child(5);
    CPPUNIT_ASSERT(2 == second_tree.size());
    second_tree.get_root_node()->insert_child(6);
    
    aTree<int> third_tree{4};
    CPPUNIT_ASSERT(third_tree.size() == 1);
    for(auto node : third_tree) {
        CPPUNIT_ASSERT(node == 4);
    }
    
    third_tree.get_root_node()->remove();
    CPPUNIT_ASSERT(third_tree.begin() == third_tree.end());
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

void aTreeTest::testNodeChildrenAmount() {
    aTree<int> tree{};
    CPPUNIT_ASSERT(tree.size() == 0);
    CPPUNIT_ASSERT(tree.add_root(2));
    
    CPPUNIT_ASSERT(tree.size() == 1);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 0);
    
    CPPUNIT_ASSERT(tree.size() == 1);
    CPPUNIT_ASSERT(tree.get_root_node()->insert_child(2) != nullptr);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 1);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[0]->amount_of_children() == 0);
    CPPUNIT_ASSERT(tree.size() == 2);
    tree.get_root_node()->get_children()[0]->remove();
    CPPUNIT_ASSERT(tree.size() == 1);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 0);
    CPPUNIT_ASSERT(tree.get_root_node()->insert_child(4) != nullptr);
    CPPUNIT_ASSERT(tree.get_root_node()->insert_child(5) != nullptr);
    CPPUNIT_ASSERT(tree.get_root_node()->insert_child(6) != nullptr);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 3);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[0]->amount_of_children() == 0);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[1]->amount_of_children() == 0);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[1]->insert_child(6) != nullptr);
    CPPUNIT_ASSERT(tree.get_root_node()->get_children()[2]->amount_of_children() == 0);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 4);
    CPPUNIT_ASSERT(tree.size() == 5);
    tree.get_root_node()->get_children()[1]->remove();
    CPPUNIT_ASSERT(tree.size() == 3);
    CPPUNIT_ASSERT(tree.get_root_node()->amount_of_children() == 2);
    tree.clear();
    CPPUNIT_ASSERT(tree.size() == 0);
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
