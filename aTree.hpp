#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>
#include <stack>
#include <utility>
#include <cstring>

// In order to create animations I need to preseve a hierarchy of bones and parts of model in form of a tree.
// Alternatively it can be achived using directed acyclic graph, but I decided to choose tree instead, because of their simplicity.
// I need to enable user to change hierarchy of model's parts.
// Most importantly I need to create a function which will traverse the tree keeping traversed nodes on a stack in order to concatenate transformations.
// Finally I want to make such structure as safe to operate with as it is possible.

namespace ms {

    template <typename T>
    struct aTree {

        struct Node {
        private:
            Node(T const & v, aTree* owner, Node * parent = nullptr);
            Node(T && v, aTree * owner, Node * parent = nullptr);
            Node(Node const &) = delete;
            Node(Node &&) = delete;
            Node & operator = (Node &&) = delete;
            Node & operator = (Node const &) = delete;
            ~Node();
            //members
            Node* parent;
            aTree* owner;
            T value;
            std::vector<Node*> children {};
        public:
            friend class aTree;
            constexpr std::vector<Node*> const get_children() const { return children; }
            constexpr Node * parent_node() const { return parent; }
            Node * insert_child(T const & value);
            Node * insert_child(T && value);
            constexpr T const & get_value() const { return value; }
            void remove();
        };

        aTree();
        aTree(aTree const &) = delete;
        aTree(aTree &&) = delete;
        aTree(T const & value);
        aTree(T && value);

        aTree & operator = (aTree &&) = delete;
        aTree & operator = (aTree const &) = delete;

        void clear();
        bool is_empty();
        bool add_root(T const & value);
        bool add_root(T && value);
        constexpr Node * get_root_node() const { return root; }
        ~aTree();

        class tree_const_iterator : public std::iterator<std::forward_iterator_tag, T> {
            public:
            friend class aTree;

            typedef tree_const_iterator iterator;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef size_t difference_type;
            typedef std::forward_iterator_tag iterator_category;

            tree_const_iterator(tree_const_iterator const &) = default;
            tree_const_iterator & operator = (tree_const_iterator const &) = default;

            ~tree_const_iterator() = default;
            iterator  operator++(int);
            iterator & operator++();
            reference operator* () const;
            pointer   operator->() const;
            iterator  operator+ (difference_type v) const;
            bool      operator==(const iterator& rhs) const;
            bool      operator!=(const iterator& rhs) const;

        private:
            tree_const_iterator(std::stack<Node *> const & stack) : stack{stack} { }
            std::stack<Node *> stack;
        };

        typedef tree_const_iterator const_iterator;

        const_iterator begin();
        const_iterator end();

    private:
        //members
        Node* root;
    };

}

template<typename T>
ms::aTree<T>::Node::Node(T const & v, aTree* owner, Node * parent) : value{v}, parent{parent}, owner{owner} {}

template<typename T>
ms::aTree<T>::Node::Node(T && v, aTree* owner, Node * parent) : value{std::forward<T>(v)}, parent{parent}, owner{owner} {}

template<typename T>
ms::aTree<T>::Node::~Node() {
    for(size_t i{0}; i < children.size(); ++i) { delete children[i]; }
}

template <typename T>
void ms::aTree<T>::Node::remove() {
    if(parent != nullptr) {
        for(size_t i{0}; i < parent->children.size(); ++i) {
            if (parent->children[i] == this) {
                parent->children.erase(parent->children.begin() + i);
                break;
            }
        }
    } else {
        owner->root = nullptr;
    }
    delete this;
}

template <typename T>
typename ms::aTree<T>::Node * ms::aTree<T>::Node::insert_child(T const & value){
    auto node = new Node{value, this->owner, this};
    children.push_back(node);
    return node;
}

template <typename T>
typename ms::aTree<T>::Node * ms::aTree<T>::Node::insert_child(T && value) {
    auto node = new Node{std::forward<T>(value), this->owner, this};
    children.push_back(node);
    return node;
}

template <typename T>
ms::aTree<T>::aTree() : root{nullptr} {}

template <typename T>
ms::aTree<T>::aTree(T && value) : root{new Node{std::forward<T>(value), this}} {}

template <typename T>
ms::aTree<T>::aTree(T const & value) : root{new Node{value, nullptr, this}} {}

template <typename T>
bool ms::aTree<T>::add_root(T const & value) {
    if (root == nullptr) {
        root = new Node{value, this, nullptr};
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool ms::aTree<T>::add_root(T && value) {
    if (root == nullptr) {
        root = new Node{std::forward<T>(value), this, nullptr};
        return true;
    } else {
        return false;
    }
}

template <typename T>
void ms::aTree<T>::clear() {
    if (root != nullptr) { delete root; root = nullptr;}
}

template <typename T>
bool ms::aTree<T>::is_empty() {
    return root == nullptr;
}

template <typename T>
typename ms::aTree<T>::const_iterator ms::aTree<T>::begin() {
    auto stack = std::stack<Node*>{};
    stack.push(root);
    return tree_const_iterator(stack);
}

template <typename T>
typename ms::aTree<T>::const_iterator ms::aTree<T>::end() {
    return tree_const_iterator(std::stack<Node*>{});
}

template <typename T>
ms::aTree<T>::~aTree() {
    if (root != nullptr) { delete root; }
}

template <typename T>
typename ms::aTree<T>::const_iterator::reference ms::aTree<T>::const_iterator::operator* () const {
    return  stack.top()->value;
}

template <typename T>
typename ms::aTree<T>::const_iterator::pointer ms::aTree<T>::const_iterator::operator->() const {
    return &stack.top()->value;
}

template <typename T>
bool ms::aTree<T>::const_iterator::operator==(const iterator& rhs) const {
    return (stack.size() == rhs.stack.size())  && (stack.top() == rhs.stack.top());
}

template <typename T>
bool ms::aTree<T>::const_iterator::operator!=(const iterator& rhs) const {
    return (stack.size() != rhs.stack.size()) || ((stack.size() == rhs.stack.size() && stack.size() > 0 && stack.top() != rhs.stack.top()));
}

template <typename T>
typename ms::aTree<T>::const_iterator::iterator & ms::aTree<T>::const_iterator::operator++ () {
    if (stack.size() > 0) {
        auto current_node = stack.top();
        stack.pop();
        auto node_iter = current_node->get_children().rbegin();
        while(node_iter != current_node->get_children().rend()) {
            stack.push(*node_iter);
            ++node_iter;
        }
    }
    return *this;
}

template <typename T>
typename ms::aTree<T>::const_iterator::iterator ms::aTree<T>::const_iterator::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename ms::aTree<T>::const_iterator::iterator ms::aTree<T>::const_iterator::operator+ (difference_type v) const {
    auto temp = *this;
    for (difference_type i {0}; i < v; ++i) {
        ++temp;
    }
    return temp;
}
