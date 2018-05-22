#include "tree_tests.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(aTreeTest);

using namespace ms;

void aTreeTest::setUp() {
    tree = new ms::tree<int>{};
    s_tree = new ms::tree<int>{};
    
    t_tree.insert_s(t_tree.end(), 1);
    t_tree.insert_c(t_tree.begin(), 0, 4);
    t_tree.insert_s(t_tree.end(), 2);
    t_tree.insert_c(++t_tree.begin(), 0, 5);
    t_tree.insert_s(t_tree.end(), 3);
    t_tree.insert_c(++(++t_tree.begin()), 0, 6);
    auto const i = t_tree.insert_c(++(++(++t_tree.begin())), 0, 7);
    t_tree.insert_s(i, 8);
    
    
}

void aTreeTest::tearDown() {
    delete tree;
    delete s_tree;
}

void aTreeTest::testParentIterator() {
//    CPPUNIT_ASSERT(t_tree.begin().parent() == t_tree.begin());
//
//    CPPUNIT_ASSERT((++t_tree.begin()).parent() == t_tree.begin());
//    CPPUNIT_ASSERT(t_tree.begin().parent().parent().parent() == t_tree.end());
//    CPPUNIT_ASSERT(t_tree.begin().parent().parent()++ == t_tree.end());
//    
//    auto i = t_tree.begin();
//    
//    CPPUNIT_ASSERT(*i = 5);
//    CPPUNIT_ASSERT(*i.parent() = 4);
//    CPPUNIT_ASSERT(*i.parent().parent() = 1);
//    
//    auto z = i.parent();
//    CPPUNIT_ASSERT(*z = 4);
//    z++;
//    CPPUNIT_ASSERT(*z == 5);
//    ++z;
//    CPPUNIT_ASSERT(*z == 2);
//    ++z;
//    CPPUNIT_ASSERT(*z == 3);
//    ++z;
//    CPPUNIT_ASSERT(z == 6);
}

void aTreeTest::testInsert() {
    auto iterator = tree->insert_s(tree->cbegin(), 2);
    CPPUNIT_ASSERT(*iterator == 2);
    auto iterator2 = tree->insert_s(tree->cbegin(), 3);
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
    
    auto itt = tree->insert_c(tree->begin(), 0, 4);
    CPPUNIT_ASSERT(*itt == 4);
    ++itt;
    CPPUNIT_ASSERT(*itt == 2);
    ++itt;
    itt = itt;
    CPPUNIT_ASSERT(itt == tree->end());
    
}

void aTreeTest::testCopyAssignment() {
    ms::tree<int> t{};
    t.insert_s(t.begin(), 2);
    t.insert_s(t.begin(), 3);
    t.insert_c(t.insert_s(t.begin(), 4), 0, 5);
    ms::tree<int> t2{};
    t2.insert_c(t2.insert_s(t2.begin(), 4), 0, 34);
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
    t.insert_s(t.begin(), 2);
    t.insert_s(t.begin(), 3);
    t.insert_s(t.begin(), 4);
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

void aTreeTest::testInsert4() {
    tree->insert_s(tree->end(), 1);
    tree->insert_c(tree->begin(), 0, 4);
    tree->insert_s(tree->end(), 2);
    tree->insert_c(++tree->begin(), 0, 5);
    tree->insert_s(tree->end(), 3);
    tree->insert_c(++(++tree->begin()), 0, 6);
    auto i = tree->insert_c(++(++(++tree->begin())), 0, 7);
    auto b = tree->begin();
    CPPUNIT_ASSERT(*b == 1);
    CPPUNIT_ASSERT(*(++b) == 4);
    CPPUNIT_ASSERT(*(++b) == 5);
    CPPUNIT_ASSERT(*(++b) == 6);
    CPPUNIT_ASSERT(*(++b) == 7);
    CPPUNIT_ASSERT(*(++b) == 2);
    CPPUNIT_ASSERT(*(++b) == 3);
}

void aTreeTest::testInsert2() {
    auto iterator = tree->insert_s(tree->cbegin(), 1);
    auto i = tree->insert_c(tree->insert_c(tree->begin(), 0, 3), 0, 2);
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
    t2.insert_s(t2.end(), 2);
    t2 = std::move(*tree);
    CPPUNIT_ASSERT(t2.size() == 3);
    CPPUNIT_ASSERT(*t2.insert_c(t2.begin(), 0, 5) == 5);
    auto it2 = t2.begin();
    CPPUNIT_ASSERT(*it2 == 1);
    it2++;
    CPPUNIT_ASSERT(*it2 == 5);
    ++it2;
    CPPUNIT_ASSERT(*it2 == 3);
    ++it2;
    CPPUNIT_ASSERT(*it2 == 2);
}

void aTreeTest::testInsert3() {
    tree->insert_s(tree->end(), 1);
    tree->insert_c(tree->begin(), 0, 4);
    tree->insert_s(tree->end(), 2);
    tree->insert_c(++(++tree->begin()), 0, 5);
    tree->insert_s(tree->end(), 3);
    tree->insert_c(++(++tree->begin()), 1, 6);
    
    auto i = tree->begin();
    CPPUNIT_ASSERT(*i == 1);
    CPPUNIT_ASSERT(*(++i) == 4);
    CPPUNIT_ASSERT(*(++i) == 2);
    CPPUNIT_ASSERT(*(++i) == 5);
}

void aTreeTest::testDeletion() {
    CPPUNIT_ASSERT(tree->erase(tree->end()) == tree->end());
    CPPUNIT_ASSERT(tree->erase(tree->insert_s(tree->begin(), 2)) == tree->end());
    CPPUNIT_ASSERT(tree->size() == 0);
    auto i1 = tree->insert_s(tree->begin(), 2);
    CPPUNIT_ASSERT(*i1 == 2);
    i1++;
    CPPUNIT_ASSERT(i1 == tree->end());
    auto i2 = tree->insert_s(tree->begin(), 3);
    CPPUNIT_ASSERT(*i2 == 3);
    i2++;
    CPPUNIT_ASSERT(*i2 == 2);
    i2++;
    CPPUNIT_ASSERT(i2 == tree->end());
    auto i3 = tree->insert_s(tree->begin(), 4);
    auto i4 = tree->insert_c(i3, 0, 123);
    auto i5 = tree->insert_c(i4, 0, 124);
    CPPUNIT_ASSERT(tree->size() == 5);
    auto iterator = tree->cbegin();
    CPPUNIT_ASSERT(*iterator == 4);
}

void aTreeTest::testSize() {
    CPPUNIT_ASSERT(tree->size() == 0);
    tree->insert_s(tree->begin(), 4);
    CPPUNIT_ASSERT(tree->size() == 1);
    tree->insert_s(tree->begin(), 5);
    CPPUNIT_ASSERT(tree->size() == 2);
    tree->insert_c(tree->begin(), 0, 5);
    CPPUNIT_ASSERT(tree->size() == 3);
    tree->clear();
    CPPUNIT_ASSERT(tree->size() == 0);
    tree->insert_s(tree->begin(), 2);
    CPPUNIT_ASSERT(tree->size() == 1);
    tree->erase(tree->begin());
    CPPUNIT_ASSERT(tree->size() == 0);
}

void aTreeTest::testEquality() {
    CPPUNIT_ASSERT(*tree == *s_tree);
    tree->insert_s(tree->begin(), 2);
    CPPUNIT_ASSERT(!(*tree == *s_tree));
    s_tree->insert_s(tree->begin(), 2);
    CPPUNIT_ASSERT(*tree == *s_tree);
}

void aTreeTest::testConstReverseIterator() {
    auto it = t_tree.crbegin();
    CPPUNIT_ASSERT(it != t_tree.crend());
    CPPUNIT_ASSERT(*t_tree.crbegin() == 3);
    ++it;
    CPPUNIT_ASSERT(*it == 2);
    it++;
    CPPUNIT_ASSERT(*it == 1);
    CPPUNIT_ASSERT(*(++it) == 4);
    CPPUNIT_ASSERT(*(++it) == 5);
    CPPUNIT_ASSERT(*(++it) == 6);
    CPPUNIT_ASSERT(*(++it) == 7);
    CPPUNIT_ASSERT(*(++it) == 8);
    CPPUNIT_ASSERT(++it == t_tree.crend());
    CPPUNIT_ASSERT(++it == t_tree.crend());
}

void aTreeTest::testParentReverseIterator() {
    CPPUNIT_ASSERT(t_tree.begin().parent().parent() == t_tree.end());
}

void aTreeTest::testReverseIterator() {
    auto it = t_tree.rbegin();
    CPPUNIT_ASSERT((--it) == t_tree.rbegin());
    CPPUNIT_ASSERT(it != t_tree.rend());
    CPPUNIT_ASSERT(*t_tree.rbegin() == 3);
    CPPUNIT_ASSERT(*(++(--(++it))) == 2);
    CPPUNIT_ASSERT(*(++(--(++it))) == 1);
    CPPUNIT_ASSERT(*(++(--(++it))) == 4);
    CPPUNIT_ASSERT(*(++(--(++it))) == 5);
    CPPUNIT_ASSERT(*(++(--(++it))) == 6);
    CPPUNIT_ASSERT(*(++(--(++it))) == 7);
    CPPUNIT_ASSERT(*(++(--(++it))) == 8);
    CPPUNIT_ASSERT((++it) == t_tree.rend());
    CPPUNIT_ASSERT(*(--it) == 8);
    auto p{it};
    CPPUNIT_ASSERT(++(--(++it)) == t_tree.rend());
    CPPUNIT_ASSERT(++it == t_tree.rend());
    CPPUNIT_ASSERT(*(--p) == 7);
    CPPUNIT_ASSERT(*(--p) == 6);
    CPPUNIT_ASSERT(*(--p) == 5);
    CPPUNIT_ASSERT(*(--p) == 4);
    CPPUNIT_ASSERT(*(--p) == 1);
    CPPUNIT_ASSERT(*(--p) == 2);
    CPPUNIT_ASSERT(*(--p) == 3);
}


void aTreeTest::testConstIterator() {
    CPPUNIT_ASSERT(tree->cbegin() == tree->cend());
    auto it = tree->cbegin();
    it = it;
    CPPUNIT_ASSERT((tree->cbegin() != tree->cend()) == false);
    
    auto i = t_tree.begin();
    CPPUNIT_ASSERT(*i == 1);
    CPPUNIT_ASSERT(*(++i) == 4);
    CPPUNIT_ASSERT(*(++i) == 5);
    CPPUNIT_ASSERT(*(++i) == 6);
    auto p = ++i;
    CPPUNIT_ASSERT(*(i) == 8);
    CPPUNIT_ASSERT(*p.parent() == 6);
    CPPUNIT_ASSERT(*((++p).parent()) == 6);
    CPPUNIT_ASSERT(*(++i) == 7);
    CPPUNIT_ASSERT(*(++i) == 2);
    CPPUNIT_ASSERT(*(++i) == 3);
}

void aTreeTest::testEmptiness() {
    CPPUNIT_ASSERT(tree->empty());
    tree->insert_s(tree->begin(), 4);
    CPPUNIT_ASSERT(!tree->empty());
    tree->clear();
    CPPUNIT_ASSERT(tree->empty());
}
