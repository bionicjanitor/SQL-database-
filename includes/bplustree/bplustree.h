#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "btree_array_funcs.h"

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *(){
           
            const bool debug = false;
            if(debug){
                cout << "before assert" << endl;
            }
            assert(it);
            if(debug){
                cout << "passed assert" << endl;
            }
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used){
            const bool debug = false;
            if(debug){
                cout << "unused ++" << endl;
            }
            Iterator temp(it, key_ptr);
            if(it){
                if(it->data_count-1 == key_ptr){
                    key_ptr = 0;
                    it = it->next;
                    
                }else if(it->data_count-1 > key_ptr){
                    key_ptr++;
                    
                }
            }
            return temp;
        }

        Iterator operator++(){
             const bool debug = false;
            if(debug){
                cout << "blank parameter ++" << endl;
            }
            if(it){
                if(it->data_count-1 == key_ptr){
                    key_ptr = 0;
                    it = it->next;
                    
                }else if(it->data_count-1 > key_ptr){
                    key_ptr++;
                    
                }
            }
            return *this;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            const bool debug = false;
            if(debug){
                cout << "== parameter" << endl;
            }
            if(lhs.it == nullptr && rhs.it == nullptr){
                return true;
            }
            if(lhs.it != nullptr && rhs.it != nullptr){
                Iterator lhs1(lhs.it, lhs.key_ptr);
                Iterator rhs1(rhs.it, rhs.key_ptr);

                if(*lhs1 == *rhs1){
                    return true;
                }
            }
            return false;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            const bool debug = false;
            if(debug){
                cout << "!= operator" << endl;
            }
            // if(lhs == rhs){
            //    return false; 
            // }
            // return true;
            return !(lhs == rhs);
        }

        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }

        bool is_null(){
            return !it;
        }

        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_leaf);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    const T&  get_existing(const T& entry) const;
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.


    


    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <typename T>
BPlusTree<T>::BPlusTree(bool dups):dups_ok(dups), data_count(0),
                                   child_count(0), next(NULL){
    const bool debug = false;
    if(debug){
        cout << "in empty constructor" << endl;

    }
    //left emtpy
}
template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = nullptr;
    for(int i = 0; i < MAXIMUM + 1; i++){
        data[i] = T();
    }
    for(int i = 0; i < MAXIMUM + 2; i++){
        subset[i] = nullptr;
    }
    for(int i = 0; i < size; i++){
        insert(a[i]);
    }
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    this->clear_tree();
    dups_ok = RHS.dups_ok;
    copy_tree(RHS);
    return *this;
}


template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){
    child_count = 0;
    data_count = other.data_count;
    copy_tree(other);
}


template <class T>
BPlusTree<T>::~BPlusTree(){
    clear_tree();
}


template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_leaf){   
    assert(empty());
    dups_ok = other.dups_ok;
    child_count = other.child_count;
    copy_array(data, other.data, data_count, other.data_count);
    if(!(other.is_leaf())){
        for(int i = 0; i < other.child_count; i++){
            BPlusTree<T>* copy_ptr = new BPlusTree<T>(); 
            subset[i] = copy_ptr; // making new btree nodes
            subset[i]->copy_tree(*other.subset[i], last_leaf); // copying it here
        }
    }
    else {
        if(last_leaf != nullptr){
            last_leaf->next = this;
        }
        last_leaf = this;
    }
}

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    //assumes this btree is empty. [memory leaks otherwise]
    clear_tree();
    BPlusTree<T>* last_leaf = nullptr;
    copy_tree(other, last_leaf);
}


template <class T>
void BPlusTree<T>::clear_tree(){
    data_count = 0;
    for(int i = 0; i < child_count; i++){
        subset[i]->clear_tree();
        delete subset[i];
        next = NULL;    
    }
    child_count = 0;
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    return Iterator(get_smallest_node());
}
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator(NULL);
}


template <class T>
void BPlusTree<T>::remove(const T& entry){

}

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    if(child_count > data_count && subset[child_count - 1] != nullptr){
        subset[child_count - 1]->print_tree(level+1);
    }
    for(int i = data_count - 1; i >= 0; i--){
        outs << setw(level*8) << "" << data[i] << endl;
        if(i < child_count && subset[i] != nullptr){
            subset[i]->print_tree(level+1);
        }
    }

}

template <class T>
void BPlusTree<T>::insert(const T& entry){
    loose_insert(entry);
    if(data_count > MAXIMUM){
        BPlusTree<T>* grow_ptr = new BPlusTree<T>();
        copy_array(grow_ptr->data, data, grow_ptr->data_count, data_count);
        copy_array(grow_ptr->subset, subset, grow_ptr->child_count, child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = grow_ptr;
        fix_excess(0);
    }
}


template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key){
    int i = first_ge(data, data_count, key);
    if(data[i] == key && i < data_count){
        if(is_leaf()){
            return Iterator(this, i);
        }
        else{
            return subset[i+1]->find(key);
        }

    }else{
        if(!is_leaf()){
            return subset[i]->find(key);
        }else{
            return Iterator(NULL, 0);
        }
    }
}


template <typename T>
T& BPlusTree<T>::get(const T& entry){
    //If entry is not in the tree, add it to the tree  
    const bool debug = false;
    if (!contains(entry)){
        insert(entry);
    }

    return get_existing(entry);
}
template <typename T>
const T& BPlusTree<T>::get(const T& entry)const{
    const bool debug = false;
    assert(contains(entry));
    return get_existing(entry);
}


template <typename T>
const T& BPlusTree<T>::get_existing(const T& entry) const{
    //assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);

}


template <typename T>
T& BPlusTree<T>::get_existing(const T& entry) {
    
    //assert that entry is not in the tree.
    //assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);

}


template <class T>
bool BPlusTree<T>::contains(const T& entry) const{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if(found){
        return true;
    }
    else if(!is_leaf()){
       return subset[i]->contains(entry);
    }
    return false;
}

template <typename T>
bool BPlusTree<T>::empty() const{
    return (data_count ==0);
}


template <typename T>
int BPlusTree<T>::size() const{
    int size = data_count;
    for(int i = 0; i < child_count; i++){
       size += subset[i]->size();
    }
    return size;
}

template <typename T>
bool BPlusTree<T>::is_valid(){
    const bool debug = false;
    // for(int i = 0; i < data_count; i++){
    //     if(data[i] > data[i+1]){
    //         return false;
    //     }
    // }
    // if(is_leaf()){ // empty tree is still valid
    //     return true;
    // }
  
    // if(data[data_count-1] > subset[child_count-1]->data[data_count-1]){
    //     return false;
    // }
    // else{
    //     return true;
    // }

    // for(int i = 0; i < data_count; i++){
    //     if(data[i] != subset[i+1]->data[0]){
    //         return false;
    //     }
    // }
    // subset->is_valid();
    return true;
}


template <typename T>
string BPlusTree<T>::in_order(){ 
    string inorder = "";
    if(data_count == 0){
        return inorder;
    }
    if(!is_leaf()){// check to see cc
        for(int i =0; i < child_count; i++){    
            inorder += subset[i]->in_order(); // left
            if(i != data_count){
               inorder +=  to_string(data[i])+ "|";  //root   
            }
        }
        return inorder;
    }else{ 
        for(int i = 0; i < data_count; i++){
            inorder +=  to_string(data[i]) + "|";   //right  
        }
        return inorder;
    }
}


template <typename T>
string BPlusTree<T>::pre_order(){
    string preorder = "";
    if(data_count == 0){
        return preorder;
    }
      if(!is_leaf()){// check to see cc
        for(int i = 0; i < child_count; i++){    
            if(i != data_count){
               preorder += to_string(data[i])+ "|";     
            }
            preorder += subset[i]->pre_order();
        }
        return preorder;
    }else{ 
        for(int i = 0; i < data_count; i++){
            preorder +=   to_string(data[i]) + "|";     
        }
        return preorder;
    }
}

template <typename T>
string BPlusTree<T>::post_order(){
    string postorder = "";
    if(data_count == 0){
        return postorder;
    }
    if(!is_leaf()){    
        postorder += subset[0]->post_order();
        for(int i = 0; i < data_count; i++){
           postorder += subset[i+1]->post_order();
           if(i != data_count){
               postorder += to_string(data[i])+ "|";  
           } 
        }
        return postorder;
    }else{ 
        for(int i = 0; i < data_count; i++){
            postorder +=   to_string(data[i]) + "|";     
        }
        return postorder;
    }
}


// template <typename T>
//  T& BPlusTree<T>::get(const T& entry){
//     assert(contains(entry));
//     return get_existing(entry);
// }


template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
    for(Iterator it = begin(); it != end(); it++){
        if(*it >= key){
            return it;
        }
    }
    return Iterator();
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
    for(Iterator it = begin(); it != end(); it++){
        if(*it > key){
            return it;
        }
    }
    return Iterator();
}



template <typename T>
T* BPlusTree<T>::find_ptr(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if(found && is_leaf()){
        return &data[i];
    }
    else if(is_leaf() && !found){
        return nullptr;
    }
    else if(!is_leaf() && found){
        return subset[i+1]->find_ptr(entry); 
    }
    else if(!is_leaf() && !found){
        return subset[i]->find_ptr(entry); 
    }
}

// template <class T>
// void BPlusTree<T>::insert(const T& entry){
//     loose_insert(entry);
//     if(data_count > MAXIMUM){
//         BPlusTree<T>* grow_ptr = new BPlusTree<T>();
//         copy_array(grow_ptr->data, data, grow_ptr->data_count, data_count);
//         copy_array(grow_ptr->subset, subset, grow_ptr->child_count, child_count);
//         data_count = 0;
//         child_count = 1;
//         subset[0] = grow_ptr;
//         fix_excess(0);
//     }
// }

template <typename T>
void BPlusTree<T>::loose_insert(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(found && is_leaf()){
        if(dups_ok){
            insert_item(data, i, data_count, entry);
        }else{
            data[i] = entry;
        }
    }
    else if(found && !is_leaf()){
        subset[i+1]->loose_insert(entry);
        fix_excess(i+1);
    } 
    else if(!found && is_leaf()){
        insert_item(data, i, data_count, entry);
    }
    else if(!found && !is_leaf()){
        subset[i]->loose_insert(entry);
        fix_excess(i);
    }
}



template <typename T> 
void BPlusTree<T>::fix_excess(int i){ 
       if(subset[i] != nullptr){
        if(subset[i]->data_count > MAXIMUM){
            BPlusTree<T>* temp = new BPlusTree<T>();  
            insert_item(subset, i+1, child_count, temp);        
            split(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);
            split(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);   
            T temp1;
            detach_item(subset[i]->data, subset[i]->data_count, temp1);
            insert_item(data, i, data_count, temp1);
            if(subset[i]->is_leaf()){
                insert_item(temp->data, 0, temp->data_count, temp1);
                temp->next = subset[i]->next;
                subset[i]->next = temp;
            }
        }
    }
}

template <typename T> 
void BPlusTree<T>::loose_remove(const T& entry){

}


template <typename T> 
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    BPlusTree *b_tree = new BPlusTree();
    



    return b_tree;
}


template <typename T> 
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    if(!is_leaf()){
        return subset[0]->get_smallest_node();
    }
    return this;
}

template <typename T> 
void BPlusTree<T>::get_smallest(T& entry){
   if(!is_leaf()){
       subset->get_smallest(entry);
   }
   else if(is_leaf()){
       entry = data[0];
   }
}     

template <typename T> 
void BPlusTree<T>::get_biggest(T& entry){

}     

template <typename T> 
void BPlusTree<T>::remove_biggest(T& entry){

}   

template <typename T> 
void BPlusTree<T>::transfer_left(int i){

}      

template <typename T> 
void BPlusTree<T>::transfer_right(int i){

}


template <typename T> 
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
    BPlusTree *b_tree = new BPlusTree();
    return b_tree;
}

#endif