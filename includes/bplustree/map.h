#ifndef MAP_H
#define MAP_H


#include "pair.h"

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator():_it(){
            
        }
        Iterator(typename map_base::Iterator it){
            _it = it;
        }
        Iterator operator ++(int unused){
            Iterator temp(_it);
            _it++;
            return temp;
        }
        Iterator operator ++(){
            return ++_it;
        }
        Pair<K, V> operator *(){
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }
    private:
        typename map_base::Iterator _it;

    };

    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);
    const V& operator[](const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not written these yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    int count(const K& key);
    Iterator lower_bound(const K& k);
    Iterator upper_bound(const K& k);

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs << print_me.map<< endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};


template <typename K, typename V>
Map<K, V>::Map(){
    key_count = 0; 
    map = new BPlusTree<Pair<K, V> >();
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin(){
    return Iterator(map.begin());
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end(){
    return Iterator(map.end());
}

template <typename K, typename V>
int Map<K, V>::size() const{
    return map.size();
}

template <typename K, typename V>
bool Map<K, V>::empty() const{
    return map.empty();
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key){
    //return at(key);
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
const V& Map<K, V>::operator[](const K& key) const{
    return map.get(Pair<K, V>(key)).value;
}

template <typename K, typename V>
V& Map<K, V>::at(const K& key){
    return map.get(Pair<K,V>(key)).value;
}

template <typename K, typename V>
const V& Map<K, V>::at(const K& key) const{
    return map.get(Pair<K,V>(key)).value; 
}

template <typename K, typename V>
void Map<K, V>::insert(const K& k, const V& v){
    Pair<K, V> pit(k, v);
    map.insert(pit);
}


template <typename K, typename V>
void Map<K, V>::erase(const K& key){

}

template <typename K, typename V>
void Map<K, V>::clear(){
    map.clear_tree();
}

template <typename K, typename V>
V Map<K, V>::get(const K& key){
    return V();
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K& key){
   return Iterator(map.find(Pair<K, V>(key)));
}

template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V>& target) const{
    return map.contains(Pair<K, V>(target));
}


template <typename K, typename V>
int Map<K, V>::count(const K& key){
    return map.size();
}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K& k){
    return Iterator(map.lower_bound(Pair<K, V>(k)));
}


template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K& k){
    return Iterator(map.upper_bound(Pair<K, V>(k)));
}
#endif