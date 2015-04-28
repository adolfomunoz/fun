#ifndef _FUNCTIONAL_LIST_ITEM_H_
#define _FUNCTIONAL_LIST_ITEM_H_

#include <utility>
#include <memory>

namespace fun {

/**
 * We avoid exceptions nor anything similar. Watch out for "head" or "rest" of empty list (segmentation fault)
 */
template<typename List>
typename List::value_type head_(const List& l)
{
    auto i = l.begin();
    return (*i);
};

template<typename List>
class Rest
{
    std::unique_ptr<List> l; typename List::const_iterator b; typename List::const_iterator e;
public:
    Rest(const List& _l) : b(_l.begin()), e(_l.end())                                {  ++b; } 
    Rest(List&& _l)      : l(std::make_unique<List>(_l)), b(*l.begin()), e(*l.end()) {  ++b; }

    using value_type     = typename List::value_type;
    using const_iterator = typename List::const_iterator;

    const_iterator begin() const { return b; }
    const_iterator end()   const { return e; }
};

template<typename List>
auto rest_(List&& l) 
{   return Rest<typename std::remove_reference<List>::type>(std::forward<List>(l)); }


template<typename List>
unsigned int length_(const List& l)
{   unsigned int size = 0;
    typename List::const_iterator i;
    for (i=l.begin();i!=l.end();++i) ++size;
    return size;
}

template<typename List>
bool null_(const List& l)
{   return l.begin() == l.end();  }

template<typename List>
bool elem_(const typename List::value_type& x, const List& l)
{
    for (auto e : l) if (e==x) return true;
    return false;
}


/**************************************
 * fun::API                           *
 **************************************/
auto head   = [] (auto&& l)           { return head_(l);   };
auto rest   = [] (auto&& l)           { return rest_(l);   };
auto length = [] (auto&& l)           { return length_(l); };
auto elem   = [] (auto&& x, auto&& l) { return elem_(x,l); };
auto null   = [] (auto&& l)           { return null_(l);   };

};

#endif
