#pragma once

#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <functional>
#include <type_traits>

namespace ms {
    
    template <class T, class A = std::allocator<T>>
    class tree {
        struct node;
    public:
        
        enum class depth_change {
            up,
            down
        };
        
        template<bool is_const, bool calls_on_hierarchy_change>
        class _iterator;
        
        using allocator_type    = A;
        using value_type        = typename A::value_type;
        using reference         = typename A::reference;
        using const_reference   = typename A::const_reference;
        using size_type         = typename A::size_type;
        
        template<bool is_const = false, bool calls_on_hierarchy_change = true>
        class _reverse_iterator {
            friend class tree;
        public:
            
            using value_type    = typename A::value_type;
            using reference     = typename std::conditional_t<is_const, T const &, T &>;
            using pointer       = typename std::conditional_t<is_const, T const *, T *>;
            using node_ptr      = node *;
            using vec_ref       = std::vector<node *> &;
            using lambda        = std::function<void(depth_change, pointer)>;
            typedef std::forward_iterator_tag       iterator_category;
            
                                        _reverse_iterator       (_iterator<is_const, calls_on_hierarchy_change> const &);
                                        _reverse_iterator       (_reverse_iterator const &) = default;
            template <bool D = !is_const>
                                        _reverse_iterator       (_reverse_iterator<D, calls_on_hierarchy_change> const &);
                                        ~_reverse_iterator      () = default;
            template <bool D = !is_const>
            _reverse_iterator &         operator =              (_reverse_iterator<D, calls_on_hierarchy_change> const &);
            _reverse_iterator &         operator =              (_reverse_iterator const &);
            bool                        operator ==             (_reverse_iterator const &) const;
            bool                        operator !=             (_reverse_iterator const &) const;
            _reverse_iterator &         operator ++             ();
            _reverse_iterator &         operator --             ();
            _reverse_iterator           operator ++             (int);
            _reverse_iterator           operator --             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            _reverse_iterator           parent                  () const;
            bool                        has_parent              () const;
            _reverse_iterator           child                   (size_type) const;
            size_type                   children_amount         () const;
            
        private:
                                        _reverse_iterator       (node_ptr, vec_ref, lambda = [](auto, auto){});
            vec_ref                     __rn;
            node_ptr                    __current;
            lambda                      __l;
        };
        
        template<bool is_const = false, bool calls_on_hierarchy_change = true>
        class _iterator {
            friend class tree;
        public:

            using value_type            = typename A::value_type;
            using reference             = typename std::conditional_t<is_const, T const &, T &>;
            using pointer               = typename std::conditional_t<is_const, T const *, T *>;
            using node_ptr              = node *;
            using vec_ref               = std::vector<node *> &;
            using lambda                = std::function<void(depth_change, pointer)>;
            typedef std::forward_iterator_tag       iterator_category;
            
                                        _iterator               (_reverse_iterator<is_const, calls_on_hierarchy_change> const &);
                                        _iterator               (_iterator const &) = default;
            template <bool D = !is_const>
                                        _iterator               (_iterator<D, calls_on_hierarchy_change> const &);
                                        ~_iterator              () = default;
            template <bool D = !is_const>
            _iterator &                 operator =              (_iterator<D, calls_on_hierarchy_change> const &);
            _iterator &                 operator =              (_iterator const &);
            bool                        operator ==             (_iterator const &) const;
            bool                        operator !=             (_iterator const &) const;
            _iterator &                 operator ++             ();
            _iterator &                 operator --             ();
            _iterator                   operator ++             (int);
            _iterator                   operator --             (int);
            reference                   operator *              () const;
            pointer                     operator ->             () const;
            _iterator                   parent                  () const;
            bool                        has_parent              () const;
            _iterator                   child                   (size_type) const;
            size_type                   children_amount         () const;

        private:
                                        _iterator               (node_ptr, vec_ref, lambda = [](auto, auto){});
            vec_ref                     __rn;
            node_ptr                    __current;
            lambda                      __l;
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
        reverse_iterator                rbegin                  (typename reverse_iterator::lambda l = [](auto, auto){});
        const_reverse_iterator          rbegin                  (typename const_reverse_iterator::lambda l = [](auto, auto){}) const;
        const_reverse_iterator          crbegin                 (typename const_reverse_iterator::lambda l = [](auto, auto){}) const;
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
            static size_type            release                 (node *);
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
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::template _iterator<is_const, calls> & ms::tree<T, A>::template _iterator<is_const, calls>::operator = (_iterator<D, calls> const & rhs) {
    static_assert(!(D == true && is_const == false), "required");
    __current = rhs.__current;
    __rn = rhs.__rn;
    if constexpr (is_const == D)
        __l = rhs.__l;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::template _iterator<is_const, calls> & ms::tree<T, A>::template _iterator<is_const, calls>::operator = (_iterator const & rhs) {
    __current = rhs.__current;
    __l = rhs.__l;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::template _reverse_iterator<is_const, calls> & ms::tree<T, A>::template _reverse_iterator<is_const, calls>::operator = (_reverse_iterator<D, calls> const & rhs) {
    static_assert(!(D == true && is_const == false), "required");
    __current = rhs.__current;
    __rn = rhs.__rn;
    if constexpr (is_const == D)
        __l = rhs.__l;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::template _reverse_iterator<is_const, calls> & ms::tree<T, A>::template _reverse_iterator<is_const, calls>::operator = (_reverse_iterator const & rhs) {
    __current = rhs.__current;
    __l = rhs.__l;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::template _iterator<is_const, calls>::_iterator (_iterator<D, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::template _iterator<is_const, calls>::_iterator (_reverse_iterator<is_const, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current}, __l{rhs.__l} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::template _reverse_iterator<is_const, calls>::_reverse_iterator (_iterator<is_const, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current}, __l{rhs.__l} { }

template<class T, class A>
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::template _reverse_iterator<is_const, calls>::_reverse_iterator (_reverse_iterator<D, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::_iterator<is_const, calls>::_iterator (node_ptr n, vec_ref rn, lambda l) : __rn{rn}, __current{n}, __l{l} {}

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::_reverse_iterator<is_const, calls>::_reverse_iterator (node_ptr n, vec_ref rn, lambda l) : __rn{rn}, __current{n}, __l{l} {}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -- () {
    if(__current == nullptr) {
        __current = !__rn.empty() ? *__rn.begin() : nullptr;
        while(!__current->__c.empty())
            __current = *__current->__c.begin();
    } else if (__current != *__rn.rbegin()) {
        auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
        auto i = std::find(nts.rbegin(), nts.rend(), __current);
        if(i == nts.rbegin()) {
            __current = __current->__p;
        } else {
            __current = *(--i);
            while(!__current->__c.empty())
                __current = *__current->__c.begin();
        }
    }
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator -- () {
    if(__current == nullptr) {
        __current = !__rn.empty() ? *__rn.rbegin() : nullptr;
        while(!__current->__c.empty())
            __current = *__current->__c.rbegin();
    } else if (__current != *__rn.rbegin()) {
        auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
        auto i = std::find(nts.begin(), nts.end(), __current);
        if(i == nts.begin()) {
            __current = __current->__p;
        } else {
            __current = *(--i);
            while(!__current->__c.empty())
                __current = *__current->__c.rbegin();
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
    for(size_type i{0}; i < t.__nodes.size(); ++i)
        __nodes[i] = node::copy(t.__nodes[i]);
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
    for(size_type i{0}; i < __nodes.size(); ++i)
        __nodes[i] = node::copy(t.__nodes[i]);
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
typename ms::tree<T, A>::size_type ms::tree<T, A>::node::release(node * n) {
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
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (ms::tree<T, A>::const_iterator it, T & value) {
    ++__size;
    if(it.__current == nullptr) {
        auto p = new node{std::move(value), nullptr};
        __nodes.push_back(p);
        return _iterator<false>{p, it.__rn};
    } else {
        auto & ip = it.__current->__p != nullptr ? it.__current->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), it.__current);
        auto n = ip.insert(p, new node{std::forward<T>(value), it.__current->__p});
        return _iterator<false>{*n, it.__rn};
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, T && value) {
    ++__size;
    if(it.__current == nullptr) {
        auto p = new node{std::forward<T>(value), nullptr};
        __nodes.push_back(p);
        return _iterator<false>{p, it.__rn};
    } else {
        auto & ip = it.__current->__p != nullptr ? it.__current->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), it.__current);
        auto n = ip.insert(p, new node{std::forward<T>(value), it.__current->__p});
        return _iterator<false>{*n, it.__rn};
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T && value) {
    if(it.__current != nullptr) {
        ++__size;
        auto parent = it.__current;
        auto t = parent->__c.insert(parent->__c.begin() + index, new node{std::forward<T>(value), parent});
        _iterator<false> iter{*t, it.__rn};
        return iter;
    } else {
        return it;
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T & value) {
    if(it.__current != nullptr) {
        ++__size;
        auto parent = it.__current;
        auto t = parent->__c.insert(parent->__c.begin() + index, new node{std::move(value), parent});
        _iterator<false> iter{*t, it.__rn};
        return iter;
    } else {
        return it;
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::erase (const_iterator iter) {
    if(iter != cend()) {
        _iterator<false> it{iter};
        if(it == cbegin()) {
            it.__current = nullptr;
        } else {
            --it;
        }
        auto & parent_children = iter.__current->__p ? iter.__current->__p->__c : __nodes;
        auto node_it = std::find_if(parent_children.begin(), parent_children.end(), [&](auto v){ return v == iter.__current; });
        __size -= node::release(*node_it);
        parent_children.erase(node_it);
        return it;
    } else {
        return iter;
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
    return iterator{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::end () const {
    return iterator{nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cend () const {
    return const_iterator{nullptr, const_cast<std::vector<node*> &>(__nodes)};
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rbegin (typename reverse_iterator::lambda l) {
    return reverse_iterator{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes, l};
}
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rbegin (typename const_reverse_iterator::lambda l) const {
    return const_reverse_iterator{!__nodes.empty() ? *__nodes.rbegin() : nullptr, __nodes, l};
}

template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crbegin (typename const_reverse_iterator::lambda l) const {
    return const_reverse_iterator(!__nodes.empty() ? *__nodes.rbegin() : nullptr, const_cast<std::vector<node*> &>(__nodes), l);
}

template<class T, class A>
typename ms::tree<T, A>::reverse_iterator ms::tree<T, A>::rend () {
    return reverse_iterator{nullptr, __nodes};
}
        
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::rend () const {
    return const_reverse_iterator{nullptr, __nodes};
}
        
template<class T, class A>
typename ms::tree<T, A>::const_reverse_iterator ms::tree<T, A>::crend () const {
    return const_reverse_iterator{nullptr, const_cast<std::vector<node*> &>(__nodes)};
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::begin () {
    return iterator{!__nodes.empty() ? *__nodes.begin() : nullptr, __nodes};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::begin () const {
    return cbegin();
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cbegin () const {
    return const_iterator{(!__nodes.empty() ? *__nodes.begin() : nullptr), const_cast<std::vector<node*> &>(__nodes)};
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls>::reference ms::tree<T, A>::_iterator<is_const, calls>::operator * () const {
    return __current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls>::pointer ms::tree<T, A>::_iterator<is_const, calls>::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
template<bool is_const, bool calls_on_hierarchy_change>
bool ms::tree<T, A>::_iterator<is_const, calls_on_hierarchy_change>::has_parent () const {
    return __current != nullptr ? (__current->__p != nullptr ? true : false) : false;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::parent () const {
    return _iterator{__current != nullptr ? (__current->__p != nullptr ? __current->__p : __current) : __current, __rn};

}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::parent () const {
    return _reverse_iterator{__current != nullptr ? (__current->__p != nullptr ? __current->__p : __current) : __current, __rn};
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_reverse_iterator<is_const, calls>::has_parent () const {
    return __current != nullptr ? (__current->__p != nullptr ? true : false) : false;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::size_type ms::tree<T, A>::_reverse_iterator<is_const, calls>::children_amount () const {
    return __current != nullptr ? __current->__nodes.size() : 0;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::child(size_type i) const {
    return _reverse_iterator{__current->__c[i]};
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls>::reference ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator * () const {
    return __current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls>::pointer ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -- (int) {
    auto t = *this;
    --(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::operator -- (int) {
    auto t = *this;
    --(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::template _reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator ++ () {
    if(__current != nullptr) {
        if(!__current->__c.empty()) {
            __current = *(__current->__c.rbegin());
            if constexpr (calls)
                __l(tree<T, A>::depth_change::down, &__current->__v);
        } else {
            while(__current != nullptr) {
                auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
                auto i = std::find(nts.begin(), nts.end(), __current);
                if(i != nts.begin()) {
                    __current = *(--i);
                    break;
                } else {
                    __current = __current->__p;
                    if constexpr (calls)
                        __l(tree<T, A>::depth_change::up, &__current->__v);
                }
            }
        }
    }
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator == (_reverse_iterator const & r) const {
    return __current == r.__current;
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator != (_reverse_iterator const & r) const {
    return __current != r.__current;
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_iterator<is_const, calls>::operator == (_iterator const & r) const {
    return __current == r.__current;
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_iterator<is_const, calls>::operator != (_iterator const & r) const {
    return __current != r.__current;
}

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::_iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator ++ () {
    if(__current != nullptr) {
        if(!__current->__c.empty()) {
            __current = *(__current->__c.begin());
            if constexpr (calls)
                __l(tree<T, A>::depth_change::down, &__current->__v);
        } else {
            while(__current != nullptr) {
                auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
                auto i = std::find(nts.rbegin(), nts.rend(), __current);
                if(i != nts.rbegin()) {
                    __current = *(--i);
                    break;
                } else {
                    __current = __current->__p;
                    if constexpr (calls)
                        __l(tree<T, A>::depth_change::up, &__current->__v);
                }
            }
        }
    }
    return *this;
}

