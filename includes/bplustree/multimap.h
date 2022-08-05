#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "multipair.h"


template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
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
        MPair<K, V> operator *(){
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

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& at(const K& key) const;
    vector<V>& at(const K& key);
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    Iterator find(const K& key);

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    int count(const K& key);
    Iterator lower_bound(const K& k);
    Iterator upper_bound(const K& k);


    bool is_valid(){
        return true;
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};


template <typename K, typename V>
MMap<K, V>::MMap(){
    mmap =  new BPlusTree<MPair<K, V> >();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin(){
    return Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end(){
    return Iterator(mmap.end());
}


template <typename K, typename V>
int MMap<K, V>::size() const{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const{
    return mmap.empty();
}

template <typename K, typename V>
const vector<V>& MMap<K, V>::at(const K& key) const{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K, V>::at(const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const{
   // MPair<K, V> pit (key);
    //return mmap.at(key);
    return mmap.get(MPair<K, V > (key)).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key){
    MPair<K, V> pit (key);
    return mmap.get(pit).value_list;
}

template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v){
    MPair<K, V> pit(k, v);
    mmap.insert(pit);
}


template <typename K, typename V>
void MMap<K, V>::erase(const K& key){
    
}

template <typename K, typename V>
void MMap<K, V>::clear(){
    mmap.clear_tree();
}

template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key){
   return Iterator(mmap.find(key));
}

template <typename K, typename V>
bool MMap<K, V>::contains(const K& key) const {
    return mmap.contains(key);
}


template <typename K, typename V>
int MMap<K, V>::count(const K& key){
    return mmap.size();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& k){
    return Iterator(mmap.lower_bound(k));
}


template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& k){
    return Iterator(mmap.upper_bound(k));
}

#endif