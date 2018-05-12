#pragma once

#include <stack>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace ms {
    
    template <class T, class A = std::allocator<T>>
    class tree {
        struct node;
    public:
        class const_iterator;
        class iterator;
        
        typedef A                               allocator_type;
        typedef typename A::value_type          value_type;
        typedef typename A::reference           reference;
        typedef typename A::const_reference     const_reference;
        typedef typename A::difference_type     difference_type;
        typedef typename A::size_type           size_type;
        
        class iterator {
            friend class tree;
            friend class const_iterator;
                                iterator        (std::stack<node*> const &);
                                iterator        (std::stack<node*> &&);
        public:

            typedef typename A::difference_type     difference_type;
            typedef typename A::value_type          value_type;
            typedef typename A::reference           reference;
            typedef typename A::pointer             pointer;
            typedef std::forward_iterator_tag       iterator_category;
            
                                iterator        (const_iterator const &);
                                iterator        (const_iterator &&);
                                iterator        (iterator const &) = default;
                                iterator        (iterator &&);
                                ~iterator       () = default;
            iterator&           operator =      (iterator const &) = default;
            bool                operator ==     (iterator const &) const;
            bool                operator !=     (iterator const &) const;
            iterator&           operator ++     ();
            iterator            operator ++     (int);
            reference           operator *      () const;
            pointer             operator ->     () const;
            
        private:
            std::stack<node*> stack;
        };
        
        class const_iterator {
            friend class tree;
            friend class iterator;
                                const_iterator  (std::stack<node*> const &);
                                const_iterator  (std::stack<node*> &&);
            public:
            
            typedef typename A::difference_type     difference_type;
            typedef typename A::value_type          value_type;
            typedef const typename A::reference     reference;
            typedef const typename A::pointer       pointer;
            typedef std::forward_iterator_tag       iterator_category;
            
                                const_iterator  (const_iterator const &) = default;
                                const_iterator  (const_iterator &&);
                                const_iterator  (iterator const  &);
                                const_iterator  (iterator &&);
                                ~const_iterator () = default;
            const_iterator &    operator =      (const const_iterator&) = default;
            bool                operator ==     (const const_iterator&) const;
            bool                operator !=     (const const_iterator&) const;
            const_iterator &    operator ++     ();
            const_iterator      operator ++     (int);
            reference           operator *      () const;
            pointer             operator ->     () const;
        private:
            std::stack<node*> stack;
        };
        
                                tree            () = default;
                                tree            (const tree&);
                                tree            (tree &&);
                                ~tree           ();
        tree &                  operator =      (const tree&);
        tree &                  operator =      (tree && t);
        bool                    operator ==     (const tree&) const;
        bool                    operator !=     (const tree&) const;
        iterator                begin           ();
        const_iterator          begin           () const;
        const_iterator          cbegin          () const;
        iterator                end             ();
        const_iterator          end             () const;
        const_iterator          cend            () const;
        iterator                insert_s        (const_iterator, const T&);
        iterator                insert_c        (const_iterator, size_type, const T&);
        iterator                erase           (const_iterator);
        void                    clear           ();
        void                    swap            (tree & t);
        constexpr size_type     size            () const { return tree_size; }
        constexpr bool          empty           () const { return tree_size == 0; }
        
    private:
        
        struct node {
            friend class tree;
        private:
            node(T const &, node * p = nullptr);
            node(T &&, node * p = nullptr);
            node(node const &) = delete;
            node(node &&) = delete;
            node & operator = (node &&) = delete;
            node & operator = (node const &) = delete;
            bool operator == (node const &);
            bool operator != (node const &);
            static std::size_t release(node *);
            static node* copy(node *);
            ~node() = default;
            T value;
            node* parent;
            std::vector<node*> children{};
        };
        
        std::vector<node*>  root_nodes{};
        size_type           tree_size{0};
    };
    
}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(std::stack<node*> const & s) : stack{s} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(iterator && rhs) : stack{std::move(rhs.stack)} { }

template<class T, class A>
ms::tree<T, A>::iterator::iterator(const_iterator const & rhs) : stack{rhs.stack} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(const_iterator && rhs) : stack{std::move(rhs.stack)} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(std::stack<node*> && s) : stack{std::move(s)} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (std::stack<node*> const & stack) : stack{stack} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (const iterator& it) : stack{it.stack} { }

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (iterator && it) : stack{std::move(it.stack)} { }

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (std::stack<node*> && s) : stack{std::move(s)} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (const_iterator && c) : stack{std::move(c.stack)} {}

template<class T, class A>
bool ms::tree<T, A>::iterator::operator == (const iterator& rhs) const {
    return (stack.size() == rhs.stack.size()) && ((stack.size() == 0) || ((stack.size() > 0) && (stack.top() == rhs.stack.top())));
}

template<class T, class A>
bool ms::tree<T, A>::iterator::operator != (const iterator& rhs) const {
    return (stack.size() != rhs.stack.size()) || ((stack.size() == rhs.stack.size() && stack.size() > 0 && stack.top() != rhs.stack.top()));
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::iterator::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class T, class A>
typename ms::tree<T, A>::iterator& ms::tree<T, A>::iterator::operator ++ () {
    if (stack.size() > 0) {
        auto const & children = (stack.top()->children);
        auto children_amount = children.size();
        stack.pop();
        for(size_t i{0}; i < children_amount; ++i) {
            stack.push(children[children_amount-1-i]);
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::iterator::reference ms::tree<T, A>::iterator::operator * () const {
    return stack.top()->value;
}

template<class T, class A>
typename ms::tree<T, A>::iterator::pointer ms::tree<T, A>::iterator::operator -> () const {
    return &stack.top()->value;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::const_iterator::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator& ms::tree<T, A>::const_iterator::operator ++ () {
    if (stack.size() > 0) {
        auto const & children = (stack.top()->children);
        auto children_amount = children.size();
        stack.pop();
        for(size_t i{0}; i < children_amount; ++i) {
            stack.push(children[children_amount-1-i]);
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator::reference ms::tree<T, A>::const_iterator::operator * () const {
    return stack.top()->value;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator::pointer ms::tree<T, A>::const_iterator::operator -> () const {
    return &stack.top()->value;
}

template<class T, class A>
bool ms::tree<T, A>::const_iterator::operator == (const const_iterator& rhs) const {
    return (stack.size() == rhs.stack.size()) && ((stack.size() == 0) || ((stack.size() > 0) && (stack.top() == rhs.stack.top())));
}

template<class T, class A>
bool ms::tree<T, A>::const_iterator::operator != (const const_iterator& rhs) const {
    return (stack.size() != rhs.stack.size()) || ((stack.size() == rhs.stack.size() && stack.size() > 0 && stack.top() != rhs.stack.top()));
}

template<class T, class A>
ms::tree<T, A>::tree (tree && t) : root_nodes{t.root_nodes}, tree_size{t.tree_size} {
    t.root_nodes.clear();
}

template<class T, class A>
ms::tree<T, A>::tree (const tree & t) : tree_size{t.tree_size} {
    root_nodes.resize(t.root_nodes.size());
    for(size_type i{0}; i < t.root_nodes.size(); ++i) {
        root_nodes[i] = node::copy(t.root_nodes[i]);
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::begin() {
    return iterator{cbegin()};
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::end() {
    return iterator({});
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cbegin() const {
    std::stack<node*> s{};
    auto it = root_nodes.rbegin();
    while(it != root_nodes.rend()) {
        s.push(*it);
        ++it;
    }
    return const_iterator{s};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cend() const {
    return const_iterator({});
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::end() const {
    return const_iterator({});
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::begin() const {
    return cbegin();
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c(const_iterator it, size_type index, const T& value) {
    if(it != cend()) {
        tree_size += 1;
        auto parent = it.stack.top();
        auto t = parent->children.insert(parent->children.begin() + index, new node{value, parent});
        iterator iter{it};
        iter.stack.pop();
        for(size_type i{0}; i < index; ++i) {
            iter.stack.pop();
        }
        iter.stack.push(*t);
        return iter;
    } else {
        return end();
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s(const_iterator it, const T& value) {
    tree_size+=1;
    if(it.stack.empty()) {
        std::stack<node*> s {};
        root_nodes.push_back(new node{value, nullptr});
        s.push(root_nodes.front());
        return iterator(s);
    } else {
        node* current_node = it.stack.top();
        if(node* parent = current_node->parent) {
            auto p = std::find(parent->children.begin(), parent->children.end(), current_node);
            auto n = root_nodes.insert(p, new node{value, parent});
            auto i{it};
            i.stack.push(*n);
            return iterator{i};
        } else {
            auto p = std::find(root_nodes.begin(), root_nodes.end(), current_node);
            auto n = root_nodes.insert(p, new node{value, nullptr});
            auto i{it};
            i.stack.push(*n);
            return iterator{i};
        }
    }
}

template<class T, class A>
bool ms::tree<T, A>::operator == (const tree& rhs) const {
    if(rhs.root_nodes.size() == root_nodes.size()) {
        bool r{true};
        for(size_type i{0}; i < root_nodes.size(); ++i)
            r = r && (*root_nodes[i] == *rhs.root_nodes[i]);
        return r;
    } else {
        return false;
    }
}

template<class T, class A>
bool ms::tree<T, A>::operator != (const tree& rhs) const {
    return !(*this == rhs);
}

template<class T, class A>
typename ms::tree<T, A>::tree & ms::tree<T, A>::operator = (tree && t) {
    std::for_each(root_nodes.begin(), root_nodes.end(), [](auto n){ node::release(n); });
    root_nodes.clear();
    root_nodes.insert(root_nodes.begin(), t.root_nodes.begin(), t.root_nodes.end());
    t.root_nodes.clear();
    tree_size = t.tree_size;
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::tree & ms::tree<T, A>::operator = (const tree & t) {
    tree_size = t.tree_size;
    std::for_each(root_nodes.begin(), root_nodes.end(), [](auto n){ node::release(n); });
    root_nodes.resize(t.root_nodes.size());
    for(size_type i{0}; i < root_nodes.size(); ++i) {
        root_nodes[i] = node::copy(t.root_nodes[i]);
    }
    return *this;
}

template<class T, class A>
void ms::tree<T, A>::swap(tree & t) {
    std::swap(root_nodes, t.root_nodes);
    std::swap(tree_size, t.tree_size);
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::erase(const_iterator iter) {
    if(iter != cend()) {
        iterator it{iter};
        it.stack.pop();
        auto & parent_children = iter.stack.top()->parent ? iter.stack.top()->parent->children : root_nodes;
        auto node_it = std::find_if(parent_children.begin(), parent_children.end(), [&](auto v){ return v == iter.stack.top(); });
        tree_size -= node::release(*node_it);
        parent_children.erase(node_it);
        return it;
    } else {
        return end();
    }
}

template<class T, class A>
void ms::tree<T, A>::clear() {
    std::for_each(root_nodes.begin(), root_nodes.end(), [](auto v){ node::release(v); });
    tree_size = 0;
    root_nodes.clear();
}

template<class T, class A>
ms::tree<T, A>::~tree() {
    for(auto _ch : root_nodes)
        node::release(_ch);
}

template<class T, class A>
ms::tree<T, A>::node::node(T const & v, node * p) : value{v}, parent{p} { }

template<class T, class A>
ms::tree<T, A>::node::node(T && v, node * p) : value(std::move(v)), parent{p} { }

template<class T, class A>
std::size_t ms::tree<T, A>::node::release(node * n) {
    std::size_t s{0};
    std::for_each(n->children.begin(), n->children.end(), [&s](auto _c){ s += release(_c); });
    delete n;
    return s + 1;
}

template<class T, class A>
typename ms::tree<T, A>::node* ms::tree<T, A>::node::copy(node * n) {
    auto new_node = new node{n->value, nullptr};
    new_node->children.resize(n->children.size());
    for(size_type i{0}; i < n->children.size(); ++i) {
        new_node->children[i] = copy(n->children[i]);
        new_node->children[i]->parent = new_node;
    }
    return new_node;
}

template<class T, class A>
bool ms::tree<T, A>::node::operator != (node const & rhs) {
    return ! (*this == rhs);
}

template<class T, class A>
bool ms::tree<T, A>::node::operator == (node const & rhs)  {
    if(value == rhs.value && children.size() == rhs.children.size()) {
        bool r{true};
        for(size_type i{0}; i < children.size(); ++i)
            r = r && (*children[i] == *rhs.children[i]);
        return r;
    } else {
        return false;
    }
}
