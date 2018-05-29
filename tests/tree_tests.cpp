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
    t_tree.begin();
    CPPUNIT_ASSERT(!t_tree.rbegin().has_parent());
    CPPUNIT_ASSERT(t_tree.rbegin().parent() == t_tree.rbegin());

    CPPUNIT_ASSERT(!t_tree.begin().has_parent());
    CPPUNIT_ASSERT(t_tree.begin().parent() == t_tree.begin());

    CPPUNIT_ASSERT((++t_tree.begin()).parent() == t_tree.begin());
    CPPUNIT_ASSERT(t_tree.begin().parent().parent().parent() == t_tree.begin());
    CPPUNIT_ASSERT(t_tree.begin().parent().parent()++ == t_tree.begin());
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
    CPPUNIT_ASSERT(*tree->insert_s(tree->end(), 1) == 1);
    CPPUNIT_ASSERT(*tree->insert_c(tree->begin(), 0, 4) == 4);
    CPPUNIT_ASSERT(*tree->insert_s(tree->end(), 2) == 2);
    CPPUNIT_ASSERT(*tree->insert_c(++(++tree->begin()), 0, 5) == 5);
    CPPUNIT_ASSERT(*tree->insert_s(tree->end(), 3) == 3);
    CPPUNIT_ASSERT(*tree->insert_c(++(++tree->begin()), 1, 6) == 6);

    auto i = tree->begin();
    CPPUNIT_ASSERT(*i == 1);
    CPPUNIT_ASSERT(*(++i) == 4);
    CPPUNIT_ASSERT(*(++i) == 2);
    CPPUNIT_ASSERT(*(++i) == 5);
}

void aTreeTest::testDeletion() {
    CPPUNIT_ASSERT(tree->erase(tree->end()) == tree->end());
    auto tmp = tree->erase(tree->insert_s(tree->begin(), 2));
    CPPUNIT_ASSERT(tmp == tree->end());
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
    CPPUNIT_ASSERT(*tree->erase(i5) == *i4);
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

void aTreeTest::testConversion() {
    ms::tree<int>::iterator b = t_tree.begin();
    ms::tree<int>::const_iterator cb{b};

    cb = b;
    
    ms::tree<int>::reverse_iterator r = t_tree.rbegin([](auto, auto){std::cout << "hello" << '\n';});
    ms::tree<int>::const_reverse_iterator cr{r};
    
    ms::tree<int>::iterator p {r};
    p = r;
    cr = r;
    
    ms::tree<int>::reverse_iterator rr {p};
    rr = p;
    CPPUNIT_ASSERT(rr == p);
}

void aTreeTest::testTreeConversionConstructor() {
    
    auto f = [](int const & a) -> float { return a; };
    auto i = [](float const & a) -> int { return a; };
    ms::tree<float> tf{t_tree, static_cast<std::function<float(int const &)>>(f)};
    ms::tree<int> ti{tf, static_cast<std::function<int(float const &)>>(i)};

    CPPUNIT_ASSERT(ti == t_tree);
}

void aTreeTest::testLambdaCalls() {
    ::tree<int> f;
    f.insert_s(f.begin(), 3);
    f.insert_s(f.begin(), 2);
    f.insert_s(f.begin(), 1);
    f.insert_c(f.begin(), 0, 11);
    f.insert_c(f.begin(), 1, 12);
    f.insert_c(f.begin().right_sibling(), 0, 22);
    f.insert_c(f.begin().right_sibling(), 1, 23);
    f.insert_c(f.begin().right_sibling().right_sibling(), 0, 33);
    f.insert_c(f.begin().right_sibling().right_sibling(), 1, 34);
    {
        int i{0};
        auto it = f.begin([&](auto a, auto b){
            if(a == ::tree<int>::depth_change::down) {
                i+=1;
            } else {
                i-=1;
            }
        });
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(*it == 1);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 11);
        --it;
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(*it == 1);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 11);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 12);
        ++it;
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(*it == 2);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 22);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 23);
        ++it;
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(*it == 3);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 33);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        CPPUNIT_ASSERT(*it == 34);

        --it;
        CPPUNIT_ASSERT(*it == 33);
        CPPUNIT_ASSERT(i == 1);
        --it;
        CPPUNIT_ASSERT(*it == 3);
        CPPUNIT_ASSERT(i == 0);
        --it;
        CPPUNIT_ASSERT(*it == 23);
        CPPUNIT_ASSERT(i == 1);
        --it;
        CPPUNIT_ASSERT(*it == 22);
        CPPUNIT_ASSERT(i == 1);
        --it;
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(i == 0);
        --it;
        CPPUNIT_ASSERT(*it == 12);
        CPPUNIT_ASSERT(i == 1);
        --it;
        CPPUNIT_ASSERT(*it == 11);
        CPPUNIT_ASSERT(i == 1);
        --it;
        CPPUNIT_ASSERT(*it == 1);
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(it == f.begin());
        CPPUNIT_ASSERT((--it) == f.begin());
    }
    {
        int i{0};
        auto it = f.rbegin([&](auto a, auto b){
            if(a == ::tree<int>::depth_change::down) {
                i+=1;
            } else {
                i-=1;
            }
        });
        CPPUNIT_ASSERT(i == 0);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(i == 0);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(i == 0);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(i == 1);
        ++it;
        CPPUNIT_ASSERT(it == f.rend());
        CPPUNIT_ASSERT(i == 0);
    }
}

void aTreeTest::testInsertTree() {
    ms::tree<int> t{};
    CPPUNIT_ASSERT(t.size() == 0);
    t.insert_s(t.begin(), 2);
    CPPUNIT_ASSERT(t.size() == 1);
    t.insert_c(t.begin(), 0, t_tree);
    CPPUNIT_ASSERT(t.insert_s(t.begin(), t) == t.end());
    CPPUNIT_ASSERT(t.size() == (t_tree.size() + 1));
    auto p = ++t.begin();
    auto p2 = t_tree.begin();
    while(p != t.end()) {
        CPPUNIT_ASSERT(*(p++) == *(p2++));
    }
    ms::tree<int> t2{};
    t2.insert_s(t2.begin(), t_tree);
    CPPUNIT_ASSERT(t2.size() == t_tree.size());
    CPPUNIT_ASSERT(t2.insert_c(t2.begin(), 0, t2) == t2.end());
    auto b = t2.begin();
    p2 = t_tree.begin();
    while(p != t.end()) {
        CPPUNIT_ASSERT(*(b++) == *(p2++));
    }
    t2.insert_s(t2.begin(), t_tree);
    CPPUNIT_ASSERT(t2.size() == 2 * t_tree.size());
    b = t2.begin();
    p2 = t_tree.begin();
    while(p2 != t.end()) {
        CPPUNIT_ASSERT(*(b++) == *(p2++));
    }
    p2 = t_tree.begin();
    while(p2 != t.end()) {
        CPPUNIT_ASSERT(*(b++) == *(p2++));
    }
    
    CPPUNIT_ASSERT(t2.size() == 2 * t_tree.size());
    auto i = t2.insert_c(t2.begin(), 0, t_tree);
    CPPUNIT_ASSERT(*i == 1);
    CPPUNIT_ASSERT(t2.size() == 3 * t_tree.size());
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
