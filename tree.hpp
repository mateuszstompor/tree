#pragma once

#include <stack>
#include <vector>
#include <cassert>
#include <algorithm>
#include <type_traits>

namespace ms {
    
    template <class T, class A = std::allocator<T>>
    class tree {
        struct node;
    public:
        
        class const_reverse_iterator;
        class reverse_iterator;
        class const_iterator;
        class iterator;
        
        typedef A                               allocator_type;
        typedef typename A::value_type          value_type;
        typedef typename A::reference           reference;
        typedef typename A::const_reference     const_reference;
        typedef typename A::size_type           size_type;
        
        class reverse_iterator {
            friend class tree;
                                        reverse_iterator        (node*, std::vector<node*>&);
        public:
            
            typedef typename A::value_type          value_type;
            typedef typename A::reference           reference;
            typedef typename A::pointer             pointer;
            typedef std::forward_iterator_tag       iterator_category;

                                        reverse_iterator    (reverse_iterator const &) = default;
                                        ~reverse_iterator   () = default;
            reverse_iterator &          operator =          (reverse_iterator const &) = default;
            bool                        operator ==         (reverse_iterator const &) const;
            bool                        operator !=         (reverse_iterator const &) const;
            reverse_iterator &          operator ++         ();
            reverse_iterator            operator ++         (int);
            reference                   operator *          () const;
            pointer                     operator ->         () const;
            reverse_iterator            parent              () const;
            
        private:
            std::vector<node *> &       __rn;
            node *                      __current;
        };
        
        class const_reverse_iterator {
            friend class tree;
            friend class reverse_iterator;
                                        const_reverse_iterator  (node const *, std::vector<node*> const &);
        public:
            
            typedef typename A::value_type          value_type;
            typedef T const &                       reference;
            typedef const T *                       pointer;
            typedef std::forward_iterator_tag       iterator_category;
            
                                        const_reverse_iterator  (const_reverse_iterator const &) = default;
                                        ~const_reverse_iterator () = default;
            const_reverse_iterator &    operator =              (const const_reverse_iterator &) = default;
            bool                        operator ==             (const const_reverse_iterator &) const;
            bool                        operator !=             (const const_reverse_iterator &) const;
            const_reverse_iterator &    operator ++             ();
            const_reverse_iterator      operator ++             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            const_reverse_iterator      parent                  () const;

        private:
            std::vector<node *> const & __rn;
            node const *                __current;
        };
        
        class iterator {
            friend class tree;
            friend class const_iterator;
                                        iterator                (std::stack<node*> const &);
                                        iterator                (std::stack<node*> &&);
        public:

            typedef typename A::value_type          value_type;
            typedef typename A::reference           reference;
            typedef typename A::pointer             pointer;
            typedef std::forward_iterator_tag       iterator_category;
            
                                        iterator                (const_iterator const & = std::stack<node*>{});
                                        iterator                (const_iterator &&);
                                        iterator                (iterator const &) = default;
                                        iterator                (iterator &&);
                                        ~iterator               () = default;
            iterator&                   operator =              (iterator const &) = default;
            bool                        operator ==             (iterator const &) const;
            bool                        operator !=             (iterator const &) const;
            iterator&                   operator ++             ();
            iterator                    operator ++             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            iterator                    parent                  () const;
            
        private:
            
            std::stack<node *>  __stack;
        };
        
        class const_iterator {
            friend class tree;
            friend class iterator;
                                        const_iterator          (std::stack<node*> const & = std::stack<node*>{});
                                        const_iterator          (std::stack<node*> &&);
            public:
            
            typedef typename A::value_type          value_type;
            typedef T const &                       reference;
            typedef const T *                       pointer;
            typedef std::forward_iterator_tag       iterator_category;
            
                                        const_iterator          (const_iterator const &) = default;
                                        const_iterator          (const_iterator &&);
                                        const_iterator          (iterator const  &);
                                        const_iterator          (iterator &&);
                                        ~const_iterator         () = default;
            const_iterator &            operator =              (const const_iterator &) = default;
            bool                        operator ==             (const const_iterator &) const;
            bool                        operator !=             (const const_iterator &) const;
            const_iterator &            operator ++             ();
            const_iterator              operator ++             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            
        private:
            
            std::stack<node *>  __stack;
        };
        
//        typedef std::reverse_iterator<reverse_iterator> reverse_iterator;
//        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        
                                        tree                    () = default;
                                        tree                    (const tree &);
                                        tree                    (tree &&);
                                        ~tree                   ();
        tree &                          operator =              (const tree&);
        tree &                          operator =              (tree &&);
        bool                            operator ==             (const tree &) const;
        bool                            operator !=             (const tree &) const;
        iterator                        begin                   ();
        const_iterator                  begin                   () const;
        const_iterator                  cbegin                  () const;
        iterator                        end                     ();
        const_iterator                  end                     () const;
        const_iterator                  cend                    () const;
        reverse_iterator                rbegin                  ();
        const_reverse_iterator          rbegin                  () const;
        const_reverse_iterator          crbegin                 () const;
        reverse_iterator                rend                    ();
        const_reverse_iterator          rend                    () const;
        const_reverse_iterator          crend                   () const;
        iterator                        insert_s                (const_iterator, const T &);
        iterator                        insert_c                (const_iterator, size_type, const T &);
        iterator                        erase                   (const_iterator);
        void                            clear                   ();
        void                            swap                    (tree &);
        constexpr size_type             size                    () const { return __size; }
        constexpr bool                  empty                   () const { return __size == 0; }
        
    private:
        
        struct node {
            friend class tree;
                                        node                    (T const &, node * p = nullptr);
                                        node                    (T &&, node * p = nullptr);
                                        node                    (node const &) = delete;
                                        node                    (node &&) = delete;
            node &                      operator =              (node &&) = delete;
            node &                      operator =              (node const &) = delete;
            bool                        operator ==             (node const &);
            bool                        operator !=             (node const &);
            static std::size_t          release                 (node *);
            static node *               copy                    (node *);
                                        ~node                   () = default;
            constexpr T const &         get_value               () const { return __v; }
            T                           __v;
            node *                      __p;
            std::vector<node *>         __c{};
        };
        
        std::vector<node *>              __nodes{};
        size_type                       __size{0};
    };
    
}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(std::stack<node*> const & s) : __stack{s} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(iterator && rhs) : __stack{std::move(rhs.__stack)} { }

template<class T, class A>
ms::tree<T, A>::iterator::iterator(const_iterator const & rhs) : __stack{rhs.__stack} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(const_iterator && rhs) : __stack{std::move(rhs.__stack)} {}

template<class T, class A>
ms::tree<T, A>::iterator::iterator(std::stack<node*> && s) : __stack{std::move(s)} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (std::stack<node*> const & s) : __stack{s} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (const iterator& i) : __stack{i.__stack} { }

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (iterator && i) : __stack{std::move(i.__stack)} { }

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (std::stack<node*> && s) : __stack{std::move(s)} {}

template<class T, class A>
ms::tree<T, A>::const_iterator::const_iterator (const_iterator && c) : __stack{std::move(c.__stack)} {}

template<class T, class A>
ms::tree<T, A>::reverse_iterator::reverse_iterator(node * n, std::vector<node*>& r) : __rn{r}, __current{n} {}

template<class T, class A>
ms::tree<T, A>::const_reverse_iterator::const_reverse_iterator (node const * n, std::vector<node*> const & rn) : __rn{rn}, __current(n) { }

template<class T, class A>
bool ms::tree<T, A>::iterator::operator == (const iterator& r) const {
    return __stack.size() == r.__stack.size() && (__stack.size() == 0 || __stack.top() == r.__stack.top());
}

template<class T, class A>
bool ms::tree<T, A>::iterator::operator != (const iterator& r) const {
    return __stack.size() != r.__stack.size() || (__stack.size() > 0 && __stack.top() != r.__stack.top());
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::iterator::operator++(int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator & ms::tree<T, A>::reverse_iterator::operator ++ () {
    if(__current != nullptr) {
        if(!__current->__c.empty()) {
            __current = *(__current->__c.rbegin());
        } else {
            while(__current != nullptr) {
                auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
                auto i = std::find(nts.begin(), nts.end(), __current);
                if(i != nts.begin()) {
                    __current = *(--i);
                    break;
                } else {
                    __current = __current->__p;
                }
            }
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::reverse_iterator::parent () const {
    return reverse_iterator{__current != nullptr ? __current->__p : nullptr, __rn};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::const_reverse_iterator::operator++(int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator & ms::tree<T, A>::const_reverse_iterator::operator ++ () {
    if(__current != nullptr) {
        if(!__current->__c.empty()) {
            __current = *(__current->__c.rbegin());
        } else {
            while(__current != nullptr) {
                auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
                auto i = std::find(nts.begin(), nts.end(), __current);
                if(i != nts.begin()) {
                    __current = *(--i);
                    break;
                } else {
                    __current = __current->__p;
                }
            }
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::const_reverse_iterator::parent () const {
    return const_reverse_iterator{__current != nullptr ? __current->__p : nullptr, __rn};
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::reverse_iterator::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
typename ms::tree<T, A>::iterator& ms::tree<T, A>::iterator::operator ++ () {
    if (__stack.size() > 0) {
        auto const & c = (__stack.top()->__c);
        auto ca = c.size();
        __stack.pop();
        for(size_type i{0}; i < ca; ++i) {
            __stack.push(c[ca-1-i]);
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::iterator::parent () const {
    if(!__stack.empty()) {
        auto t{*this};
        auto p = t.__stack.top()->__p;
        while(!t.__stack.empty() && t.__stack.top()->__p == p)
            t.__stack.pop();
        if(p) {
            t.__stack.push(p);
        }
        return t;
    }
    return *this;
};

template<class T, class A>
typename ms::tree<T, A>::iterator::reference ms::tree<T, A>::iterator::operator * () const {
    return __stack.top()->__v;
}

template<class T, class A>
typename ms::tree<T, A>::iterator::pointer ms::tree<T, A>::iterator::operator -> () const {
    return &__stack.top()->__v;
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator::reference ms::tree<T, A>::const_reverse_iterator::operator * () const {
    return this->__current->__v;
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator::pointer ms::tree<T, A>::const_reverse_iterator::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator::reference ms::tree<T, A>::reverse_iterator::operator * () const {
    return __current->__v;
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator::pointer ms::tree<T, A>::reverse_iterator::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::const_iterator::operator++(int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator& ms::tree<T, A>::const_iterator::operator ++ () {
    if (__stack.size() > 0) {
        auto const & c = (__stack.top()->c);
        auto ca = c.size();
        __stack.pop();
        for(size_type i{0}; i < ca; ++i) {
            __stack.push(c[ca-1-i]);
        }
    }
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator::reference ms::tree<T, A>::const_iterator::operator * () const {
    return __stack.top()->__v;
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator::pointer ms::tree<T, A>::const_iterator::operator -> () const {
    return &__stack.top()->value;
}

template<class T, class A>
bool ms::tree<T, A>::const_iterator::operator == (const const_iterator& r) const {
    return __stack.size() == r.__stack.size() && (__stack.size() == 0 || __stack.top() == r.__stack.top());
}

template<class T, class A>
bool ms::tree<T, A>::const_iterator::operator != (const const_iterator& r) const {
    return __stack.size() != r.__stack.size() || (__stack.size() > 0 && __stack.top() != r.__stack.top());
}

template<class T, class A>
bool ms::tree<T, A>::const_reverse_iterator::operator == (const const_reverse_iterator & r) const {
    return __current == r.__current;
}

template<class T, class A>
bool ms::tree<T, A>::const_reverse_iterator::operator != (const const_reverse_iterator & r) const {
    return __current != r.__current;
}

template<class T, class A>
bool ms::tree<T, A>::reverse_iterator::operator == (const reverse_iterator& r) const {
    return __current == r.__current;
}

template<class T, class A>
bool ms::tree<T, A>::reverse_iterator::operator != (const reverse_iterator& r) const {
    return __current != r.__current;
}

template<class T, class A>
ms::tree<T, A>::tree (tree && t) : __nodes{t.__nodes}, __size{t.__size} {
    t.__nodes.clear();
}

template<class T, class A>
ms::tree<T, A>::tree (const tree & t) : __size{t.__size} {
    __nodes.resize(t.__nodes.size());
    for(size_type i{0}; i < t.__nodes.size(); ++i) {
        __nodes[i] = node::copy(t.__nodes[i]);
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::begin() {
    return iterator{cbegin()};
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::end() {
    return iterator{};
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rbegin() {
    return reverse_iterator{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rbegin() const {
    return const_reverse_iterator{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rend() {
    return reverse_iterator{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rend() const {
    return const_reverse_iterator{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crend () const {
    return const_reverse_iterator{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crbegin () const {
    return const_reverse_iterator{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cbegin() const {
    std::stack<node*> s{};
    auto it = __nodes.rbegin();
    while(it != __nodes.rend()) {
        s.push(*it);
        ++it;
    }
    return const_iterator{s};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cend() const {
    return const_iterator{};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::end() const {
    return const_iterator{};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::begin() const {
    return cbegin();
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c(const_iterator it, size_type index, const T& value) {
    if(it != cend()) {
        ++__size;
        auto parent = it.__stack.top();
        auto t = parent->__c.insert(parent->__c.begin() + index, new node{value, parent});
        iterator iter{std::move(it)};
        iter.__stack.pop();
        for(size_type i{0}; i < index; ++i) {
            iter.__stack.pop();
        }
        iter.__stack.push(*t);
        return iter;
    } else {
        return end();
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s(const_iterator it, const T& value) {
    ++__size;
    if(it.__stack.empty()) {
        std::stack<node*> s {};
        __nodes.push_back(new node{value, nullptr});
        s.push(__nodes.front());
        return iterator{s};
    } else {
        auto current_node = it.__stack.top();
        auto & ip = current_node->__p != nullptr ? current_node->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), current_node);
        auto n = ip.insert(p, new node{value, current_node->__p});
        iterator i{std::move(it)};
        i.__stack.push(*n);
        return i;
    }
}

template<class T, class A>
bool ms::tree<T, A>::operator == (const tree& rhs) const {
    if(rhs.__nodes.size() == __nodes.size()) {
        bool r{true};
        for(size_type i{0}; i < __nodes.size(); ++i)
            r = r && (*__nodes[i] == *rhs.__nodes[i]);
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
    std::for_each(__nodes.begin(), __nodes.end(), [](auto n){ node::release(n); });
    __nodes.clear();
    __nodes.insert(__nodes.begin(), t.__nodes.begin(), t.__nodes.end());
    t.__nodes.clear();
    __size = t.__size;
    return *this;
}

template<class T, class A>
typename ms::tree<T, A>::tree & ms::tree<T, A>::operator = (const tree & t) {
    __size = t.__size;
    std::for_each(__nodes.begin(), __nodes.end(), [](auto n){ node::release(n); });
    __nodes.resize(t.__nodes.size());
    for(size_type i{0}; i < __nodes.size(); ++i) {
        __nodes[i] = node::copy(t.__nodes[i]);
    }
    return *this;
}

template<class T, class A>
void ms::tree<T, A>::swap(tree & t) {
    std::swap(__nodes, t.__nodes);
    std::swap(__size, t.__size);
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::erase(const_iterator iter) {
    if(iter != cend()) {
        iterator it{iter};
        it.__stack.pop();
        auto & parent_children = iter.__stack.top()->__p ? iter.__stack.top()->__p->__c : __nodes;
        auto node_it = std::find_if(parent_children.begin(), parent_children.end(), [&](auto v){ return v == iter.__stack.top(); });
        __size -= node::release(*node_it);
        parent_children.erase(node_it);
        return it;
    } else {
        return end();
    }
}

template<class T, class A>
void ms::tree<T, A>::clear() {
    std::for_each(__nodes.begin(), __nodes.end(), [](auto v){ node::release(v); });
    __size = 0;
    __nodes.clear();
}

template<class T, class A>
ms::tree<T, A>::~tree() {
    for(auto _ch : __nodes)
        node::release(_ch);
}

template<class T, class A>
ms::tree<T, A>::node::node(T const & v, node * p) : __v{v}, __p{p} { }

template<class T, class A>
ms::tree<T, A>::node::node(T && v, node * p) : __v(std::move(v)), __p{p} { }

template<class T, class A>
std::size_t ms::tree<T, A>::node::release(node * n) {
    std::size_t s{0};
    std::for_each(n->__c.begin(), n->__c.end(), [&](auto _c){ s += node::release(_c); });
    delete n;
    return s + 1;
}

template<class T, class A>
typename ms::tree<T, A>::node* ms::tree<T, A>::node::copy(node * n) {
    auto new_node = new node{n->__v, nullptr};
    new_node->__c.resize(n->__c.size());
    for(size_type i{0}; i < n->__c.size(); ++i) {
        new_node->__c[i] = copy(n->__c[i]);
        new_node->__c[i]->__p = new_node;
    }
    return new_node;
}

template<class T, class A>
bool ms::tree<T, A>::node::operator != (node const & r) {
    return !(*this == r);
}

template<class T, class A>
bool ms::tree<T, A>::node::operator == (node const & rhs)  {
    if(__v == rhs.__v && __c.size() == rhs.__c.size()) {
        bool r{true};
        for(size_type i{0}; i < __c.size(); ++i)
            r = r && (*__c[i] == *rhs.__c[i]);
        return r;
    } else {
        return false;
    }
}
