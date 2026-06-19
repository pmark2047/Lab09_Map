/***********************************************************************
 * Header:
 *    MAP
 * Summary:
 *    Our custom implementation of a std::map 
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        map                 : A class that represents a map
 *        map::iterator       : An iterator through a map
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include "pair.h"     // for pair
#include "bst.h"      // no nested class necessary for this assignment

#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug

namespace custom
{

/*****************************************************************
 * MAP
 * Create a Map, similar to a Binary Search Tree
 *****************************************************************/
template <class K, class V>
class map
{
public:
   using Pairs = custom::pair<K, V>;

   // 
   // Construct
   //
   map() 
   {
   }
   map(const map &  rhs) 
   {
       bst = (rhs.bst);              // use BST copy constructor
   }
   map(map && rhs) 
   {
       bst = std::move(rhs.bst);     // use BST move constructor
   }
   template <class Iterator>
   map(Iterator first, Iterator last) 
   {
       // loop through the range
       for (auto it = first; it != last; it++)
           bst.insert(*it, true);    // add using BST's insert function
   }
   map(const std::initializer_list <Pairs>& il) 
   {
       // loop through the list
       for (const auto & p : il)     // add using BST's insert function
           bst.insert(p, true);
   }
  ~map()         
   {
   }

   //
   // Assign
   //
   map & operator = (const map & rhs) 
   {
       clear();
       bst = rhs.bst;               // use BST operators
       return *this;
   }
   map & operator = (map && rhs)
   {
       clear();
       bst.swap(rhs.bst);           // use BST swap
       return *this;
   }
   map & operator = (const std::initializer_list <Pairs> & il)
   {
       clear();
       for (const auto &p : il)
           bst.insert(p);           // use BST insert
      return *this;
   }
   
   // 
   // Iterator
   //
   class iterator;
   iterator begin() 
   { 
      return iterator(bst.begin()); // find the first item in bst
   }
   iterator end() 
   { 
      return iterator(bst.end());   // find the last item in bst
   }

   // 
   // Access
   //
   const V & operator [] (const K & k) const;
         V & operator [] (const K & k);
   const V & at (const K& k) const;
         V & at (const K& k);
   iterator find(const K & k)
   {
      return iterator();
   }

   //
   // Insert
   //
   custom::pair<typename map::iterator, bool> insert(Pairs && rhs)
   {
      return make_pair(iterator(), true);
   }
   custom::pair<typename map::iterator, bool> insert(const Pairs & rhs)
   {
      return make_pair(iterator(), true);
   }

   template <class Iterator>
   void insert(Iterator first, Iterator last)
   {
   }
   void insert(const std::initializer_list <Pairs>& il)
   {
   }

   //
   // Remove
   //
   void clear() noexcept
   {
   }
   size_t erase(const K& k);
   iterator erase(iterator it);
   iterator erase(iterator first, iterator last);

   //
   // Status
   //
   bool empty() const noexcept 
   { 
      return bst.empty();
   }
   size_t size() const noexcept 
   { 
      return bst.size();
   }


#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   // the students DO NOT need to use a nested class
   BST < pair <K, V >> bst;
};


/**********************************************************
 * MAP ITERATOR
 * Forward and reverse iterator through a Map, just call
 * through to BSTIterator
 *********************************************************/
template <typename K, typename V>
class map <K, V> :: iterator
{
public:
   //
   // Construct
   //
   iterator()
   {
   }
   iterator(const typename BST < pair <K, V> > :: iterator & rhs)
   {
       it = rhs;
   }
   iterator(const iterator & rhs) 
   {
       it = rhs.it;
   }

   //
   // Assign
   //
   iterator & operator = (const iterator & rhs)
   {
       it = rhs.it;
      return *this;
   }

   //
   // Compare
   //
   bool operator == (const iterator & rhs) const 
   { 
      return it == rhs.it;
   }
   bool operator != (const iterator & rhs) const 
   {
      return it != rhs.it;
   }

   // 
   // Access
   //
   const pair <K, V> & operator * () const
   {
      return *it;
   }

   //
   // Increment
   //
   iterator & operator ++ ()
   {
       // increment and return
       ++it;
      return *this;
   }
   iterator operator ++ (int postfix)
   {
       // return value
       iterator temp(*this);
       // increment
       ++it;
       // return unchanged value
      return temp;
   }
   iterator & operator -- ()
   {
       // decrement and return
       --it;
      return *this;
   }
   iterator  operator -- (int postfix)
   {
       // return value
       iterator temp(*this);
       // decrement
       --it;
       // return unchanged value
      return temp;
   }

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   // Member variable
   typename BST < pair <K, V >>  :: iterator it;   
};


/*****************************************************
 * MAP :: SUBSCRIPT
 * Retrieve an element from the map
 ****************************************************/
template <typename K, typename V>
V& map <K, V> :: operator [] (const K& key)
{
    // create new pair with given key
    pair<K, V> p(key, V());
    // make a bst iterator
    typename BST<Pairs>::iterator it = bst.find(p);
    // is it empty? no:
    if (it != bst.end())
        return const_cast<V&>((*it).second);    // return second value
    // yes:
    else
    {
        // add value to map
        bst.insert(p, true);
        return const_cast<V&>((*bst.find(p)).second); // return the second value
    }
   //return *(new V);
}

/*****************************************************
 * MAP :: SUBSCRIPT
 * Retrieve an element from the map
 ****************************************************/
template <typename K, typename V>
const V& map <K, V> :: operator [] (const K& key) const
{
   return *(new V);
}

/*****************************************************
 * MAP :: AT
 * Retrieve an element from the map
 ****************************************************/
template <typename K, typename V>
V& map <K, V> ::at(const K& key)
{
    // create new pair with given key
    pair<K, V> p(key, V());
    // make a bst iterator
    typename BST<Pairs>::iterator it = bst.find(p);
    // is it empty? no:
    if (it != bst.end())
        return const_cast<V&>((*it).second);    // return second value
    // yes:
    else
        throw std::out_of_range("invalid map<K, T> key");
}

/*****************************************************
 * MAP :: AT
 * Retrieve an element from the map
 ****************************************************/
template <typename K, typename V>
const V& map <K, V> ::at(const K& key) const
{
   return *(new V);
}

/*****************************************************
 * SWAP
 * Swap two maps
 ****************************************************/
template <typename K, typename V>
void swap(map <K, V>& lhs, map <K, V>& rhs)
{
    lhs.bst.swap(rhs.bst);
}

/*****************************************************
 * ERASE
 * Erase one element
 ****************************************************/
template <typename K, typename V>
size_t map<K, V>::erase(const K& k)
{
   return size_t(99);
}

/*****************************************************
 * ERASE
 * Erase several elements
 ****************************************************/
template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator first, map<K, V>::iterator last)
{
   return iterator();
}

/*****************************************************
 * ERASE
 * Erase one element
 ****************************************************/
template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator it)
{
   return iterator();
}

}; //  namespace custom

