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
    
    #ifndef TESTS
            struct node;
    #endif
        
        template<class X, class Y>
        friend class tree;
        
        enum class sibling {
            left,
            right
        };
        
        template<class D>
        static D                        get_sibling             (D, sibling);
        
        template<class D>
        static bool                     has_sibling             (D, sibling);
        
    public:
        
    #ifdef TESTS
            struct node;
    #endif
        
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
            
            using value_type            = typename A::value_type;
            using reference             = typename std::conditional_t<is_const, T const &, T &>;
            using pointer               = typename std::conditional_t<is_const, T const *, T *>;
            using node_ptr              = node *;
            using vec_ref               = std::vector<node *> &;
            using lambda                = std::function<void(depth_change, _reverse_iterator)>;
            using iterator_category     = std::forward_iterator_tag;
            
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
            _reverse_iterator           left_sibling            () const;
            bool                        has_left_sibling        () const;
            _reverse_iterator           right_sibling           () const;
            bool                        has_right_sibling       () const;
            _reverse_iterator           child                   (size_type) const;
            size_type                   children_amount         () const;
    #ifndef TESTS
        private:
    #endif
                                        _reverse_iterator       (node_ptr, vec_ref, lambda = [](auto, auto){});
            vec_ref                     __rn;
            node_ptr                    __current;
            lambda                      __l{[](auto, auto){}};
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
            using lambda                = std::function<void(depth_change, _iterator)>;
            using iterator_category     = std::forward_iterator_tag;
            
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
            _iterator                   left_sibling            () const;
            bool                        has_left_sibling        () const;
            _iterator                   right_sibling           () const;
            bool                        has_right_sibling       () const;
            _iterator                   child                   (size_type) const;
            size_type                   children_amount         () const;
    #ifndef TESTS
        private:
    #endif
                                        _iterator               (node_ptr, vec_ref, lambda = [](auto, auto){});
            vec_ref                     __rn;
            node_ptr                    __current;
            lambda                      __l{[](auto, auto){}};
        };
        
        using iterator                  = _iterator<false>;
        using const_iterator            = _iterator<true>;
        using reverse_iterator          = _reverse_iterator<false>;
        using const_reverse_iterator    = _reverse_iterator<true>;
        
                                        tree                    () = default;
                                        tree                    (const tree &);
                                        tree                    (tree &&);
        template <class U>
                                        tree                    (tree<U> const &, std::function<T(U const &)>);
                                        ~tree                   ();
        tree &                          operator =              (const tree &);
        tree &                          operator =              (tree &&);
        bool                            operator ==             (const tree &) const;
        bool                            operator !=             (const tree &) const;
        iterator                        begin                   (typename iterator::lambda = [](auto, auto){});
        const_iterator                  begin                   (typename const_iterator::lambda = [](auto, auto){}) const;
        const_iterator                  cbegin                  (typename const_iterator::lambda = [](auto, auto){}) const;
        iterator                        end                     ();
        const_iterator                  end                     () const;
        const_iterator                  cend                    () const;
        reverse_iterator                rbegin                  (typename reverse_iterator::lambda = [](auto, auto){});
        const_reverse_iterator          rbegin                  (typename const_reverse_iterator::lambda = [](auto, auto){}) const;
        const_reverse_iterator          crbegin                 (typename const_reverse_iterator::lambda = [](auto, auto){}) const;
        reverse_iterator                rend                    ();
        const_reverse_iterator          rend                    () const;
        const_reverse_iterator          crend                   () const;
        iterator                        insert_s                (const_iterator, T const &);
        iterator                        insert_s                (const_iterator, T &&);
        iterator                        insert_s                (const_iterator, tree const &);
        iterator                        insert_c                (const_iterator, size_type, T const &);
        iterator                        insert_c                (const_iterator, size_type, T &&);
        iterator                        insert_c                (const_iterator, size_type, tree const &);
        iterator                        erase                   (const_iterator);
        void                            clear                   ();
        void                            swap                    (tree &);
        constexpr size_type             size                    () const { return __size; }
        constexpr bool                  empty                   () const { return __size == 0; }
#ifndef TESTS
    private:
#endif
        
        struct node {
            friend class tree;
                                        node                    (T const &, node *, node *, node *);
                                        node                    (T &&, node *, node *, node *);
                                        node                    (node const &) = delete;
                                        node                    (node &&) = delete;
            node &                      operator =              (node &&) = delete;
            node &                      operator =              (node const &) = delete;
            bool                        operator ==             (node const &);
            bool                        operator !=             (node const &);
            static size_type            release                 (node *);
            
            template <class X> static typename
            ms::tree<X>::node *         copy                    (node * n, std::function<X(T const &)> l = [](auto a){return a;});
                                        ~node                   () = default;
            constexpr T const &         get_value               () const { return __v; }
            T                           __v;
            node *                      __p;
            node *                      __l;
            node *                      __r;
            std::vector<node *>         __c{};
        };
        
        std::vector<node *>             __nodes{};
        size_type                       __size{0};
    };
    
}

template<class T, class A>
template<class __iterator_class>
bool ms::tree<T, A>::has_sibling (__iterator_class it, sibling s) {
    if(it.__current != nullptr) {
        auto v = it.__current->__p == nullptr ? it.__rn : it.__current->__p->__c;
        size_type i = std::find(v.begin(), v.end(), it.__current) - v.begin();
        return s == sibling::left ? i > 0 : i < v.size() - 1;
    }
    return false;
}

template<class T, class A>
template<class __iterator_class>
__iterator_class ms::tree<T, A>::get_sibling (__iterator_class it, sibling s) {
    if(it.__current != nullptr) {
        auto v = it.__current->__p == nullptr ? it.__rn : it.__current->__p->__c;
        auto i = std::find(v.begin(), v.end(), it.__current);
        return __iterator_class{*(s == sibling::left ? --i : ++i), it.__rn, it.__l};
    } else {
        return it;
    }
}

template<class T, class A>
template<bool is_const, bool calls>
template<bool D>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator = (_iterator<D, calls> const & rhs) {
    static_assert(!(D == true && is_const == false), "required");
    __current = rhs.__current;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator = (_iterator const & rhs) {
    __current = rhs.__current;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
template<bool D>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator = (_reverse_iterator<D, calls> const & rhs) {
    static_assert(!(D == true && is_const == false), "required");
    __current = rhs.__current;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator = (_reverse_iterator const & rhs) {
    __current = rhs.__current;
    __rn = rhs.__rn;
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls>::_iterator (_iterator<D, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls>::_iterator (_reverse_iterator<is_const, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls>::_reverse_iterator (_iterator<is_const, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
template <bool D>
ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls>::_reverse_iterator (_reverse_iterator<D, calls> const & rhs) : __rn{rhs.__rn}, __current{rhs.__current} { }

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::_iterator<is_const, calls>::_iterator (node_ptr n, vec_ref rn, lambda l) : __rn{rn}, __current{n}, __l{l} {}

template<class T, class A>
template<bool is_const, bool calls>
ms::tree<T, A>::_reverse_iterator<is_const, calls>::_reverse_iterator (node_ptr n, vec_ref rn, lambda l) : __rn{rn}, __current{n}, __l{l} {}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -- () {
    if(__current == nullptr) {
        __current = !__rn.empty() ? *__rn.begin() : nullptr;
        while(!__current->__c.empty())
            __current = *__current->__c.begin();
    } else if (__current != *__rn.rbegin()) {
        auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
        auto i = std::find(nts.rbegin(), nts.rend(), __current);
        if(i == nts.rbegin()) {
            __current = __current->__p;
            if constexpr (calls) {
                __l(tree<T, A>::depth_change::up, *this);
            }
        } else {
            __current = *(--i);
            while(!__current->__c.empty()) {
                __current = *__current->__c.begin();
                __l(tree<T, A>::depth_change::down, *this);
            }
        }
    }
    return *this;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator -- () {
    if(__current == nullptr) {
        __current = !__rn.empty() ? *__rn.rbegin() : nullptr;
        while(!__current->__c.empty())
            __current = *__current->__c.rbegin();
    } else if (__current != *__rn.begin()){
        auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
        auto i = std::find(nts.begin(), nts.end(), __current);
        if(i == nts.begin()) {
            __current = __current->__p;
            if constexpr (calls) {
                __l(tree<T, A>::depth_change::up, *this);
            }
        } else {
            __current = *(--i);
            while(!__current->__c.empty()) {
                __current = *__current->__c.rbegin();
                __l(tree<T, A>::depth_change::down, *this);
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
template <class U>
ms::tree<T, A>::tree (tree<U> const & t, std::function<T(U const &)> l) {
    __nodes.resize(t.__nodes.size());
    for(size_type i{0}; i < t.__nodes.size(); ++i) {
        __nodes[i] = tree<U>::node::
		
		#ifndef __WIN32__
		template
		#endif
		
		copy<T>(t.__nodes[i], l);
        if(i > 0) {
            __nodes[i - 1]->__r = __nodes[i];
            __nodes[i]->__l = __nodes[i - 1];
        }
    }
}

template<class T, class A>
ms::tree<T, A>::tree (const tree & t) : __size{t.__size} {
    __nodes.resize(t.__nodes.size());
    for(size_type i{0}; i < t.__nodes.size(); ++i) {
        __nodes[i] = node::
		
		#ifndef __WIN32__
		template
		#endif

        copy<T>(t.__nodes[i]);
        if(i > 0) {
            __nodes[i - 1]->__r = __nodes[i];
            __nodes[i]->__l = __nodes[i - 1];
        }
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
typename ms::tree<T, A> & ms::tree<T, A>::operator = (tree && t) {
    std::for_each(__nodes.begin(), __nodes.end(), [](auto n){ node::release(n); });
    __nodes.clear();
    __nodes.insert(__nodes.begin(), t.__nodes.begin(), t.__nodes.end());
    t.__nodes.clear();
    __size = t.__size;
    return *this;
}

template<class T, class A>
typename ms::tree<T, A> & ms::tree<T, A>::operator = (const tree & t) {
    __size = t.__size;
    std::for_each(__nodes.begin(), __nodes.end(), [](auto n){ node::release(n); });
    __nodes.resize(t.__nodes.size());
    for(size_type i{0}; i < __nodes.size(); ++i) {
        __nodes[i] = node::
		
		#ifndef __WIN32__
		template
		#endif

		copy<T>(t.__nodes[i]);
    
        if(i > 0) {
            __nodes[i - 1]->__r = __nodes[i];
            __nodes[i]->__l = __nodes[i - 1];
        }
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
ms::tree<T, A>::node::node(T const & v, node * p, node * l, node * r) : __v{v}, __p{p}, __l{l}, __r{r} { }

template<class T, class A>
ms::tree<T, A>::node::node(T && v, node * p, node * l, node * r) : __v(std::move(v)), __p{p}, __l{l}, __r{r} { }

template<class T, class A>
typename ms::tree<T, A>::size_type ms::tree<T, A>::node::release(node * n) {
    size_type s{0};
    std::for_each(n->__c.begin(), n->__c.end(), [&](auto _c){ s += node::release(_c); });
    delete n;
    return s + 1;
}


template<class T, class A>
template <class X>
#ifndef __WIN32__
typename ::ms::tree<X>::node *
#else
typename ms::tree<X>::node *
#endif
ms::tree<T, A>::node::copy (node * n, std::function<X(T const &)> l) {
    auto new_node = new typename ms::tree<X>::node{l(n->__v), nullptr, nullptr, nullptr};
    new_node->__c.resize(n->__c.size());
    for(size_type i{0}; i < n->__c.size(); ++i) {
        new_node->__c[i] = copy<X>(n->__c[i], l);
        new_node->__c[i]->__p = new_node;
        if(i > 0) {
            new_node->__c[i]->__l = new_node->__c[i-1];
            new_node->__c[i-1]->__r = new_node;
        }
    }
    return new_node;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, T const & value) {
    ++__size;
    if(it.__current == nullptr) {
        auto p = new node{value, nullptr, nullptr, nullptr};
        if(__size > 1) {
            (*__nodes.rbegin())->__r = p;
            p->__l = *__nodes.rbegin();
        }
        __nodes.push_back(p);
        return _iterator<false>{p, it.__rn};
    } else {
        auto & ip = it.__current->__p != nullptr ? it.__current->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), it.__current);
        auto node_to_insert = new node{value, it.__current->__p, (*p)->__l, (*p)};
        if(node_to_insert->__l) {
            node_to_insert->__l->__r = node_to_insert;
        }
        if(node_to_insert->__r) {
            node_to_insert->__r->__l = node_to_insert;
        }
        auto n = ip.insert(p, node_to_insert);
        return _iterator<false>{*n, it.__rn};
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, T && value) {
    ++__size;
    if(it.__current == nullptr) {
        auto p = new node{std::forward<T>(value), nullptr, nullptr, nullptr};
        if(__size > 1) {
            (*__nodes.rbegin())->__r = p;
            p->__l = *__nodes.rbegin();
        }
        __nodes.push_back(p);
        return _iterator<false>{p, it.__rn};
    } else {
        auto & ip = it.__current->__p != nullptr ? it.__current->__p->__c : __nodes;
        auto p = std::find(ip.begin(), ip.end(), it.__current);
        auto node_to_insert = new node{std::forward<T>(value), it.__current->__p, (*p)->__l, (*p)};
        if(node_to_insert->__l) {
            node_to_insert->__l->__r = node_to_insert;
        }
        if(node_to_insert->__r) {
            node_to_insert->__r->__l = node_to_insert;
        }
        auto n = ip.insert(p, node_to_insert);
        return _iterator<false>{*n, it.__rn};
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_s (const_iterator it, tree const & t) {
    if(this != &t) {
        __size += t.__size;
        if(it.__current == nullptr) {
            for(size_type i{0}; i < t.__nodes.size(); ++i) {
                __nodes.push_back(node::
					
					#ifndef __WIN32__
					template
					#endif

					copy<T>(t.__nodes[i]));
                if(i > 0 || (i == 0 && __nodes.size() > 0)) {
                    __nodes[i]->__l = __nodes[i - 1];
                    __nodes[i - 1]->__r = __nodes[i];
                }
            }
            return _iterator<false>{__nodes.front(), it.__rn};
        } else {
            auto & ip = it.__current->__p != nullptr ? it.__current->__p->__c : __nodes;
            auto index = std::find(ip.begin(), ip.end(), it.__current) - ip.begin();
            auto i = t.__nodes.rbegin();
            while(i != t.__nodes.rend()) {
                auto n = node::
					
					#ifndef __WIN32__
					template
					#endif
					
					copy<T>(*i);
                n->__p = it.__current->__p;
                if(index > 0 && index < ip.size() - 1) {
                    ip[index]->__l = n;
                    n->__r = ip[index];
                    ip[index-1]->__r = n;
                    n->__l = ip[index-1];
                }
                ip.insert(index + ip.begin(), n);
                ++i;
            }
            return _iterator<false>{*(ip.begin() + index), it.__rn};
        }
    } else {
        return end();
    }
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T && value) {
    if(it.__current != nullptr) {
        ++__size;
        auto parent = it.__current;
        auto node_to_insert = new node{std::forward<T>(value), parent, nullptr, nullptr};
        if(!parent->__c.empty()) {
            auto l = index > 0 ? parent->__c[index-1] : nullptr;
            auto r = index < parent->__c.size() ? parent->__c[index] : nullptr;
            node_to_insert->__l = l;
            node_to_insert->__r = r;
            if(l) {
                l->__r = node_to_insert;
            }
            if(r) {
                r->__l = node_to_insert;
            }
        }
        auto t = parent->__c.insert(parent->__c.begin() + index, node_to_insert);
        _iterator<false> iter{*t, it.__rn};
        return iter;
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, T const & value) {
    if(it.__current != nullptr) {
        ++__size;
        auto parent = it.__current;
        auto node_to_insert = new node{value, parent, nullptr, nullptr};
        if(!parent->__c.empty()) {
            auto l = index > 0 ? parent->__c[index-1] : nullptr;
            auto r = index < parent->__c.size() ? parent->__c[index] : nullptr;
            node_to_insert->__l = l;
            node_to_insert->__r = r;
            if(l) {
                l->__r = node_to_insert;
            }
            if(r) {
                r->__l = node_to_insert;
            }
        }
        auto t = parent->__c.insert(parent->__c.begin() + index, node_to_insert);
        _iterator<false> iter{*t, it.__rn};
        return iter;
    }
    return it;
}

template<class T, class A>
typename ms::tree<T, A>::iterator ms::tree<T, A>::insert_c (const_iterator it, size_type index, tree const & t) {
    if(this != &t && it.__current != nullptr) {
        __size += t.__size;
        auto parent = it.__current;
        for(size_type i{0}; i < t.__nodes.size(); ++i) {
            auto cp = node::
            
                #ifndef __WIN32__
                template
                #endif

                copy<T>(t.__nodes[i]);
            cp->__p = parent;
            if(index + i > 0) {
                cp->__l = parent->__c[index + i - 1];
                parent->__c[index + i - 1]->__r = cp;
            }
            if(i == t.__nodes.size() - 1 && index < parent->__c.size() - 2) {
                cp->__r = parent->__c[index + i + 1];
                parent->__c[index + i + 1]->__l = cp;
            }
            parent->__c.insert(parent->__c.begin() + index + i, cp);
        }
        _iterator<false> iter{*(parent->__c.begin() + index), it.__rn};
        return iter;
    } else {
        return end();
    }
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
        if((*node_it)->__l) {
            (*node_it)->__l = (*node_it)->__r;
        }
        if((*node_it)->__r) {
            (*node_it)->__r = (*node_it)->__l;
        }
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
typename ms::tree<T, A>::iterator ms::tree<T, A>::begin (typename iterator::lambda l) {
    return iterator{!__nodes.empty() ? *__nodes.begin() : nullptr, __nodes, l};
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::begin (typename const_iterator::lambda l) const {
    return cbegin(l);
}

template<class T, class A>
typename ms::tree<T, A>::const_iterator ms::tree<T, A>::cbegin (typename const_iterator::lambda l) const {
    return const_iterator{(!__nodes.empty() ? *__nodes.begin() : nullptr), const_cast<std::vector<node*> &>(__nodes), l};
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls>::reference ms::tree<T, A>::_iterator<is_const, calls>::operator * () const {
    return __current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls>::pointer ms::tree<T, A>::_iterator<is_const, calls>::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
template<bool is_const, bool calls_on_hierarchy_change>
bool ms::tree<T, A>::_iterator<is_const, calls_on_hierarchy_change>::has_parent () const {
    return __current != nullptr ? (__current->__p != nullptr ? true : false) : false;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::parent () const {
    return _iterator{__current != nullptr ? (__current->__p != nullptr ? __current->__p : __current) : __current, __rn};

}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_iterator<is_const, calls>::has_left_sibling () const {
    return ms::tree<T, A>::has_sibling(*this, sibling::left);
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_reverse_iterator<is_const, calls>::has_left_sibling () const {
    return ms::tree<T, A>::has_sibling(*this, sibling::left);
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::right_sibling () const {
    return ms::tree<T, A>::get_sibling(*this, sibling::right);
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::left_sibling () const {
    return ms::tree<T, A>::get_sibling(*this, sibling::left);
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::right_sibling () const {
    return ms::tree<T, A>::get_sibling(*this, sibling::right);
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::left_sibling () const {
    return ms::tree<T, A>::get_sibling(*this, sibling::left);
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_iterator<is_const, calls>::has_right_sibling () const {
    return ms::tree<T, A>::has_sibling(*this, sibling::right);
}

template<class T, class A>
template<bool is_const, bool calls>
bool ms::tree<T, A>::_reverse_iterator<is_const, calls>::has_right_sibling () const {
    return ms::tree<T, A>::has_sibling(*this, sibling::right);
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::parent () const {
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
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::child(size_type i) const {
    return _reverse_iterator{__current->__c[i]};
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls>::reference ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator * () const {
    return __current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls>::pointer ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -> () const {
    return &__current->__v;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator ++ (int) {
    auto t = *this;
    ++(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator -- (int) {
    auto t = *this;
    --(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> ms::tree<T, A>::_iterator<is_const, calls>::operator -- (int) {
    auto t = *this;
    --(*this);
    return t;
}

template<class T, class A>
template<bool is_const, bool calls>
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_reverse_iterator<is_const, calls> & ms::tree<T, A>::_reverse_iterator<is_const, calls>::operator ++ () {
    if(__current != nullptr) {
        if(!__current->__c.empty()) {
            __current = *(__current->__c.rbegin());
            if constexpr (calls)
                __l(tree<T, A>::depth_change::down, *this);
        } else {
            while(__current != nullptr) {
                auto & nts = __current->__p != nullptr ? __current->__p->__c : __rn;
                auto i = std::find(nts.begin(), nts.end(), __current);
                if(i != nts.begin()) {
                    __current = *(--i);
                    break;
                } else {
                    __current = __current->__p;
                    if constexpr (calls) {
                        if(__current != nullptr)
                            __l(tree<T, A>::depth_change::up, *this);
                    }
                        
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
typename ms::tree<T, A>::

#ifndef __WIN32__
template
#endif

_iterator<is_const, calls> & ms::tree<T, A>::_iterator<is_const, calls>::operator ++ () {
    if(__current) {
        if(__current->__c.empty()) {
            while(__current != nullptr) {
                if(__current->__r != nullptr) {
                    __current = __current->__r;
                    break;
                }
                __current = __current->__p;
                if constexpr (calls) {
                    if(__current != nullptr)
                        __l(tree<T, A>::depth_change::up, *this);
                }
            }
        } else {
            __current = __current->__c[0];
            if constexpr (calls)
                __l(tree<T, A>::depth_change::down, *this);
        }
    }
    return *this;
}

