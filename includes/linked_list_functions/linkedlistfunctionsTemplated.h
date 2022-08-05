#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H

#include "../node/node.h"

// declarations 

using namespace std;

template <typename T>
void _print_list(node<T>* head);

template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*&head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);


//Linked List General Functions definitions:

template <typename T>
void _print_list(node<T>* head){
node<T>* walker = head;
    while(walker != nullptr){
        cout << "<-[" << *walker << "]->";
        walker = walker->_next; 
    }
    cout << "|||" << endl;
}


//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){

}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    const bool debug = true;
    if(debug){
        cout << "using search_list" << endl;
    }
    node<T>* walker = head;
    while(walker != nullptr){
        if(walker->_item == key){
        return walker;
        }
    walker = walker->_next;
    }
    return nullptr;
}


template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    // const bool debug = true;
    // if(debug){
    //     cout << "using _insert_head" << endl;
    // }
    node<T>* insert_pointer = new node<T>(insert_this, head);
    if(head != nullptr){
    head->_prev = insert_pointer;
    }
    head = insert_pointer; 
    return head; 
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    //   const bool debug = true;
    // if(debug){
    //     cout << "using _insert_head" << endl;
    // }
    if(head == nullptr || after_this == nullptr){
        head = _insert_head(head, insert_this);
        return head;
    }else{
        node<T>* insert_pointer = new node<T>(insert_this);   
        insert_pointer->_next = after_this->_next;
        insert_pointer->_prev = after_this;
        after_this->_next = insert_pointer;
        return insert_pointer;
    } 
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    if(before_this == head || before_this == nullptr){
        head = _insert_head(head, insert_this); 
        return head;
    }
    node<T>* before_pointer = new node<T>(insert_this);
    before_pointer->_next = before_this;
    before_pointer->_prev = before_this->_prev;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    // const bool debug = true;
    // if(debug){
    //     cout << "using _previous_node" << endl;
    // }
    // if(prev_to_this == head){
    //     return nullptr; 
    // }
    // node<T>* previous_ptr = head;
    // while(previous_ptr != nullptr){
    //     if(previous_ptr->_next == prev_to_this){
    //         return previous_ptr; 
    //     }
    //     previous_ptr = previous_ptr->_next;
    // }
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    const bool debug = false;
    if(debug){
        cout << "using _delete_node" << endl;
    }
    T temp = delete_this->_item;
    if(delete_this == head){
        head = head->_next;
    }else{
    node<T>* delete_pointer = delete_this->_prev;
    delete_pointer->_next = delete_this->_next;
    }
    delete delete_this;
    return temp;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    if(head == nullptr){
    //cout << "source is an empty list...sorry"<< endl;
    return nullptr;
    }
    node<T>* dest = new node<T>(); //creating new separate list
    node<T>* new_node;
    node<T>* d_ptr = dest; //pointer to new list
    node<T>* source = head; // pointer to source
    d_ptr->_item = source->_item; // making heads equal to each other
    source = source->_next; //pointing to _next node in source
    while(source != nullptr){
        new_node = _insert_after(dest, d_ptr, source->_item);
        d_ptr = d_ptr->_next; //->|||
        source = source->_next;
    }
    return dest;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    const bool debug = false;
    if(debug){
        cout << "using _clear_list" << endl;
    }
    node<T>* clear_pointer = head;
    // node<T>* clear_ahead;
    //cout << "clearing the list(s)" << endl;
    while(clear_pointer != nullptr){
        // delete clear_pointer;       
        //clear_ahead = clear_pointer->_next;
        _delete_node(clear_pointer, clear_pointer);
        //clear_pointer = clear_ahead;
    }
    delete clear_pointer;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
       const bool debug = true;
    if(debug){
        cout << "using _at" << endl;
    }
    node<T>* walker = head;
    int count = 0;
    while(count != pos){        
        walker = walker -> _next;
        count++;
    }
    return walker->_item;
}
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
     const bool debug = true;
     node<T> *walker = src;
    if(src != nullptr) {
        dest = _insert_head(dest, walker->_item);
        node<T>* dest_walker = dest;
        walker = walker->_next;
        while (walker != nullptr) {
            _insert_after(dest, dest_walker, walker->_item);
            if (dest_walker->_next == nullptr) {
                return dest_walker;
            }

            dest_walker = dest_walker->_next;
            walker = walker->_next;
        }
        return dest_walker;
    }
    return nullptr;
}
#endif // LINKEDLISTFUNCTIONSTEMPLATED_H