#include "tree_tests.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(aTreeTest);

using namespace ms;

void aTreeTest::setUp() {
    tree = new ms::tree<int>{};
    s_tree = new ms::tree<int>{};
}

void aTreeTest::tearDown() {
    delete tree;
    delete s_tree;
}

void aTreeTest::testInsert() {
    auto iterator = tree->insert_sibling(tree->cbegin(), 2);
    CPPUNIT_ASSERT(*iterator == 2);
    auto iterator2 = tree->insert_sibling(tree->cbegin(), 3);
    CPPUNIT_ASSERT(*iterator == 2);
    CPPUNIT_ASSERT(*iterator2 == 3);
    iterator2++;
    CPPUNIT_ASSERT(iterator2 != tree->end());
    CPPUNIT_ASSERT(*iterator2 == 2);
    ++iterator2;
    CPPUNIT_ASSERT(iterator2 == tree->end());
    
    auto const_iter = tree->cbegin();
    CPPUNIT_ASSERT(const_iter != tree->cend());
    CPPUNIT_ASSERT(const_iter == tree->begin());
    CPPUNIT_ASSERT((const_iter != tree->begin()) == false);
    
    auto itt = tree->insert_child(tree->begin(), 0, 4);
    CPPUNIT_ASSERT(*itt == 4);
    ++itt;
    CPPUNIT_ASSERT(*itt == 2);
    ++itt;
    itt = itt;
    CPPUNIT_ASSERT(itt == tree->end());
    
}

void aTreeTest::testCopyAssignment() {
    ms::tree<int> t{};
    t.insert_sibling(t.begin(), 2);
    t.insert_sibling(t.begin(), 3);
    t.insert_child(t.insert_sibling(t.begin(), 4), 0, 5);
    ms::tree<int> t2{};
    t2.insert_child(t2.insert_sibling(t2.begin(), 4), 0, 34);
    t2 = t;
    auto it_t2 = t2.begin();
    auto it_t = t.begin();
    CPPUNIT_ASSERT(t2.size() == t.size());
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(it_t == t.end());
    CPPUNIT_ASSERT(it_t2 == t2.end());
}

void aTreeTest::testCopyConstructor() {
    auto t{*tree};
    CPPUNIT_ASSERT(t == *tree);
    t.insert_sibling(t.begin(), 2);
    t.insert_sibling(t.begin(), 3);
    t.insert_sibling(t.begin(), 4);
    auto t2{t};
    auto it_t2 = t2.begin();
    auto it_t = t.begin();
    CPPUNIT_ASSERT(t2.size() == t.size());
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(*it_t2 == *it_t);
    CPPUNIT_ASSERT(&(*it_t2) != &(*it_t));
    it_t++;
    ++it_t2;
    CPPUNIT_ASSERT(it_t == t.end());
    CPPUNIT_ASSERT(it_t2 == t2.end());
}

void aTreeTest::testInsert2() {
    auto iterator = tree->insert_sibling(tree->cbegin(), 1);
    auto i = tree->insert_child(tree->insert_child(tree->begin(), 0, 3), 0, 2);
    CPPUNIT_ASSERT(*i == 2);
    ++i;
    CPPUNIT_ASSERT(i == tree->end());
    
    auto beg = tree->begin();
    CPPUNIT_ASSERT(*beg == 1);
    beg++;
    CPPUNIT_ASSERT(*beg == 3);
    beg++;
    CPPUNIT_ASSERT(*beg == 2);
    beg++;
    CPPUNIT_ASSERT(beg == tree->end());
    beg++;
    CPPUNIT_ASSERT(beg == tree->end());
    ms::tree<int> t2{};
    t2.insert_sibling(t2.end(), 2);
    t2 = std::move(*tree);
    CPPUNIT_ASSERT(t2.size() == 3);
    CPPUNIT_ASSERT(*t2.insert_child(t2.begin(), 0, 5) == 5);
    auto it2 = t2.begin();
    CPPUNIT_ASSERT(*it2 == 1);
    it2++;
    CPPUNIT_ASSERT(*it2 == 5);
    ++it2;
    CPPUNIT_ASSERT(*it2 == 3);
    ++it2;
    CPPUNIT_ASSERT(*it2 == 2);
}

void aTreeTest::testDeletion() {
    CPPUNIT_ASSERT(tree->erase(tree->end()) == tree->end());
    CPPUNIT_ASSERT(tree->erase(tree->insert_sibling(tree->begin(), 2)) == tree->end());
    CPPUNIT_ASSERT(tree->size() == 0);
    auto i1 = tree->insert_sibling(tree->begin(), 2);
    CPPUNIT_ASSERT(*i1 == 2);
    i1++;
    CPPUNIT_ASSERT(i1 == tree->end());
    auto i2 = tree->insert_sibling(tree->begin(), 3);
    CPPUNIT_ASSERT(*i2 == 3);
    i2++;
    CPPUNIT_ASSERT(*i2 == 2);
    i2++;
    CPPUNIT_ASSERT(i2 == tree->end());
    auto i3 = tree->insert_sibling(tree->begin(), 4);
    auto i4 = tree->insert_child(i3, 0, 123);
    auto i5 = tree->insert_child(i4, 0, 124);
    CPPUNIT_ASSERT(tree->size() == 5);
    auto iterator = tree->cbegin();
    CPPUNIT_ASSERT(*iterator == 4);

    
    
    
//    auto it = tree->erase(tree->begin());
//    CPPUNIT_ASSERT(tree->size() == 2);
//    CPPUNIT_ASSERT(it != tree->end());
}

void aTreeTest::testSize() {
    CPPUNIT_ASSERT(tree->size() == 0);
    tree->insert_sibling(tree->begin(), 4);
    CPPUNIT_ASSERT(tree->size() == 1);
    tree->insert_sibling(tree->begin(), 5);
    CPPUNIT_ASSERT(tree->size() == 2);
    tree->insert_child(tree->begin(), 0, 5);
    CPPUNIT_ASSERT(tree->size() == 3);
    tree->clear();
    CPPUNIT_ASSERT(tree->size() == 0);
    tree->insert_sibling(tree->begin(), 2);
    CPPUNIT_ASSERT(tree->size() == 1);
    tree->erase(tree->begin());
    CPPUNIT_ASSERT(tree->size() == 0);
}

void aTreeTest::testEquality() {
    CPPUNIT_ASSERT(*tree == *s_tree);
    tree->insert_sibling(tree->begin(), 2);
    CPPUNIT_ASSERT(!(*tree == *s_tree));
    s_tree->insert_sibling(tree->begin(), 2);
    CPPUNIT_ASSERT(*tree == *s_tree);
}

void aTreeTest::testConstIterator() {
    CPPUNIT_ASSERT(tree->cbegin() == tree->cend());
    auto it = tree->cbegin();
    it = it;
    CPPUNIT_ASSERT((tree->cbegin() != tree->cend()) == false);
}

void aTreeTest::testEmptiness() {
    CPPUNIT_ASSERT(tree->empty());
    tree->insert_sibling(tree->begin(), 4);
    CPPUNIT_ASSERT(!tree->empty());
    tree->clear();
    CPPUNIT_ASSERT(tree->empty());
}
