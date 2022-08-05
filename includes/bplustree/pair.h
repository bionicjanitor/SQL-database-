#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <vector>

#include "bplustree.h"
template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){    
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
        outs << print_me.key << ": "  << print_me.value;
        return outs; 
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        // if(lhs.key == rhs.key && lhs.value == rhs.value){
        //     return true;
        // }
        // if(lhs.key == rhs.key){
        //     if(lhs.value != rhs.value){
        //         return false;
        //     }else{
        //         return true;
        //     }
        // }

        return lhs.key == rhs.key;

    }
    friend bool operator !=(const Pair<K, V>& lhs, const Pair<K, V>& rhs){

        // if(lhs.key != rhs.key && lhs.value != rhs.value){
        //     return true;
        // }
        // if(lhs.key == rhs.key){
        //     if(lhs.value != rhs.value){
        //         return true;
        //     }else{
        //         return false;
        //     }
        // }

        return lhs.key != rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return lhs.key >= rhs.key;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
        return rhs;
    }
};







#endif