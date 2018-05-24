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
        
        typedef A                               allocator_type;
        typedef typename A::value_type          value_type;
        typedef typename A::reference           reference;
        typedef typename A::const_reference     const_reference;
        typedef typename A::size_type           size_type;
        
        template<bool Const = false>
        class _reverse_iterator {
            friend class tree;
        public:
            
            using value_type    = typename A::value_type;
            using reference     = typename std::conditional_t<Const, T const &, T &>;
            using pointer       = typename std::conditional_t<Const, T const *, T *>;
            using node_ptr      = typename std::conditional_t<Const, node const *, node *>;
            using vec_ref       = typename std::conditional_t<Const, std::vector<node *> const &, std::vector<node *> &>;
            
            typedef std::forward_iterator_tag       iterator_category;
            
                                        _reverse_iterator   (node_ptr, vec_ref);
                                        _reverse_iterator   (_reverse_iterator const &) = default;
                                        ~_reverse_iterator  () = default;
            _reverse_iterator &          operator =         (_reverse_iterator const &) = default;
            bool                        operator ==         (_reverse_iterator const &) const;
            bool                        operator !=         (_reverse_iterator const &) const;
            _reverse_iterator &         operator ++         ();
            _reverse_iterator &         operator --         ();
            _reverse_iterator           operator ++         (int);
            reference                   operator *          () const;
            pointer                     operator ->         () const;
            _reverse_iterator           parent              () const;
            _reverse_iterator           child               (size_type) const;
            
        private:
            vec_ref                     __rn;
            node_ptr                    __current;
        };
        
        template<bool Const = false>
        class _iterator {
            friend class tree;
                                        _iterator                (std::vector<node *> const *, std::stack<node*> const &);
                                        _iterator                (std::vector<node *> const *, std::stack<node*> &&);
        public:

            using value_type            = typename A::value_type;
            using reference             = typename std::conditional_t< Const, T const &, T & >;
            using pointer               = typename std::conditional_t< Const, T const *, T * >;
            
            typedef std::forward_iterator_tag       iterator_category;
            
                                        template <bool D = !Const>
                                        _iterator               (_iterator<D> const &);
                                        _iterator               (_iterator const &);
                                        _iterator               (_iterator &&);
                                        ~_iterator              () = default;
            _iterator&                  operator =              (_iterator const &) = default;
            bool                        operator ==             (_iterator const &) const;
            bool                        operator !=             (_iterator const &) const;
            _iterator&                  operator ++             ();
            _iterator                   operator ++             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            _iterator                   parent                  () const;

        private:
            std::vector<node *> const * __rn;
            std::stack<node *>          __stack;
        };
        
        using iterator                  = _iterator<false>;
        using const_iterator            = _iterator<true>;
        using reverse_iterator          = _reverse_iterator<false>;
        using const_reverse_iterator    = _reverse_iterator<true>;
        
                                        tree                    () = default;
                                        tree                    (const tree &);
                                        tree                    (tree &&);
                                        ~tree                   ();
        tree &                          operator =              (const tree &);
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
        iterator                        insert_s                (const_iterator, T &);
        iterator                        insert_s                (const_iterator, T &&);
        iterator                        insert_c                (const_iterator, size_type, T &);
        iterator                        insert_c                (const_iterator, size_type, T &&);
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
        
        std::vector<node *>             __nodes{};
        size_type                       __size{0};
    };
    
}

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_iterator<Const>::_iterator (std::vector<node *> const * r, std::stack<node*> const & s) : __rn{r}, __stack{s} {}

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_iterator<Const>::_iterator (std::vector<node *> const * r, std::stack<node*> && s) : __rn{r}, __stack{std::forward<std::stack<node*>>(s)} {}

template<class T, class A>
template<bool Const>
template<bool D>
ms::tree<T, A>::_iterator<Const>::_iterator (_iterator<D> const & rhs) : __rn{rhs.__rn}, __stack{rhs.__stack} {}

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_iterator<Const>::_iterator (_iterator const & rhs) : __rn{rhs.__rn}, __stack{rhs.__stack} {}

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_iterator<Const>::_iterator (_iterator && rhs) : __rn{rhs.__rn}, __stack{std::move(rhs.__stack)} { }

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_reverse_iterator<Const>::_reverse_iterator (node_ptr n, vec_ref rn) : __rn{rn}, __current{n} {}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const> & ms::tree<T, A>::_reverse_iterator<Const>::operator -- () {
    if(__current == nullptr) {
        __current = !__rn.empty() ? *__rn.begin() : nullptr;
        while(!__current->__c.empty()) {
            __current = *__current->__c.begin();
        }
    } else if (__current != *__rn.rbegin()) {
        auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
        auto i = std::find(nts.rbegin(), nts.rend(), __current);
        if(i == nts.rbegin()) {
            __current = __current->__p;
        } else {
            __current = *(--i);
            while(!__current->__c.empty()) {
                __current = *__current->__c.begin();
            }
        }
    }
    return *this;
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
    size_type s{0};
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
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, T & value) {
    ++__size;
    if(it.__stack.empty()) {
        std::stack<node*> s {};
        __nodes.push_back(new node{std::forward<T>(value), nullptr});
        s.push(__nodes.front());
        return _iterator<false>{it.__rn, s};
    } else {
        auto current_node = it.__stack.top();
        auto & ip = current_node->__p != nullptr ? current_node->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), current_node);
        auto n = ip.insert(p, new node{std::forward<T>(value), current_node->__p});
        _iterator<false> i{it.__rn, it.__stack};
        i.__stack.push(*n);
        return i;
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T && value) {
    if(it != cend()) {
        ++__size;
        auto parent = it.__stack.top();
        auto t = parent->__c.insert(parent->__c.begin() + index, new node{std::forward<T>(value), parent});
        _iterator<false> iter{it.__rn, std::move(it.__stack)};
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
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, T && value) {
    ++__size;
    if(it.__stack.empty()) {
        std::stack<node*> s {};
        __nodes.push_back(new node{std::forward<T>(value), nullptr});
        s.push(__nodes.front());
        return _iterator<false>{it.__rn, s};
    } else {
        auto current_node = it.__stack.top();
        auto & ip = current_node->__p != nullptr ? current_node->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), current_node);
        auto n = ip.insert(p, new node{std::forward<T>(value), current_node->__p});
        _iterator<false> i{it.__rn, it.__stack};
        i.__stack.push(*n);
        return i;
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T & value) {
    if(it != cend()) {
        ++__size;
        auto parent = it.__stack.top();
        auto t = parent->__c.insert(parent->__c.begin() + index, new node{value, parent});
        _iterator<false> iter{it.__rn, it.__stack};
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
typename ms::tree<T, A>::iterator ms::tree<T, A>::erase (const_iterator iter) {
    if(iter != cend()) {
        _iterator<false> it{iter};
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

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::end () {
    return _iterator<false>{&__nodes, {}};
    
}


template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::end () const {
    return _iterator<true>{&__nodes, {}};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cend () const {
    return _iterator<true>{&__nodes, {}};
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rbegin () {
    return _reverse_iterator<false>{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes};
}
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rbegin () const {
    return _reverse_iterator<true>{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crbegin () const {
    return _reverse_iterator<true>(!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes);
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rend                    () {
    return _reverse_iterator<false>{nullptr, __nodes};
}
        
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rend () const {
    return _reverse_iterator<true>{nullptr, __nodes};
}
        
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crend () const {
    return _reverse_iterator<true>{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::begin () {
    std::stack<node*> s{};
    auto it = __nodes.rbegin();
    while(it != __nodes.rend()) {
        s.push(*it);
        ++it;
    }
    return _iterator<false>{&__nodes, s};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::begin () const {
    return cbegin();
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cbegin () const {
    std::stack<node*> s{};
    auto it = __nodes.rbegin();
    while(it != __nodes.rend()) {
        s.push(*it);
        ++it;
    }
    return _iterator<true>{&__nodes, s};
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _iterator<Const> ms::tree<T, A>::_iterator<Const>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _iterator<Const>::reference ms::tree<T, A>::_iterator<Const>::operator * () const {
    return __stack.top()->__v;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _iterator<Const>::pointer ms::tree<T, A>::_iterator<Const>::operator -> () const {
    return &__stack.top()->__v;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _iterator<Const> ms::tree<T, A>::_iterator<Const>::parent () const {
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
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const> ms::tree<T, A>::_reverse_iterator<Const>::parent () const {
    return reverse_iterator{__current != nullptr ? __current->__p : nullptr, __rn};
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const> ms::tree<T, A>::_reverse_iterator<Const>::child(size_type i) const {
    return reverse_iterator{__current->__c[i]};
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const>::reference ms::tree<T, A>::_reverse_iterator<Const>::operator * () const {
    return __current->__v;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const>::pointer ms::tree<T, A>::_reverse_iterator<Const>::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const> ms::tree<T, A>::_reverse_iterator<Const>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool Const>
typename ms::tree<T, A>::template _reverse_iterator<Const> & ms::tree<T, A>::_reverse_iterator<Const>::operator ++ () {
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
template<bool Const>
bool ms::tree<T, A>::_reverse_iterator<Const>::operator == (_reverse_iterator const & r) const {
    return __current == r.__current;
}

template<class T, class A>
template<bool Const>
bool ms::tree<T, A>::_reverse_iterator<Const>::operator != (_reverse_iterator const & r) const {
    return __current != r.__current;
}

template<class T, class A>
template<bool Const>
bool ms::tree<T, A>::_iterator<Const>::operator == (_iterator const & r) const {
    return __stack.size() == r.__stack.size() && (__stack.size() == 0 || __stack.top() == r.__stack.top());
}

template<class T, class A>
template<bool Const>
bool ms::tree<T, A>::_iterator<Const>::operator !=             (_iterator const & r) const {
    return __stack.size() != r.__stack.size() || (__stack.size() > 0 && __stack.top() != r.__stack.top());
}

template<class T, class A>
template<bool Const>
ms::tree<T, A>::_iterator<Const> & ms::tree<T, A>::_iterator<Const>::operator ++ () {
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

