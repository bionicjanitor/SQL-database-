#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"


template <typename T>
class Queue
{
public:
    class Iterator{
    public:
    Iterator(){                     //default ctor
            _ptr = nullptr;
        }                  
        Iterator(node<T>* p){        //Point Iterator to where
            _ptr = p;                  //  p is pointing to
        }                              
        operator bool(){                //casting operator: true if _ptr not NULL
            if(_ptr != nullptr){          //this turned out to be a pain!
                return true;
            }                                          
            return false;
        }                                


        T& operator *(){  //dereference operator 
            return _ptr->_item;
        }                       
        T* operator ->(){  //member access operator
           return &_ptr->_item;
        }                       

        bool is_null(){
            if(_ptr == nullptr){
                return true;
            }
            return false;
        }                                 //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right){       //true if left != right
            if(left._ptr != right._ptr){
                return true;
            }
            return false;
        }
                                 

        friend bool operator ==(const Iterator& left, const Iterator& right){//true if left == right
           if(left._ptr == right._ptr){
               return true;
           } 
           return false;
        }
                                 

        Iterator& operator++(){         //member operator: ++it; or ++it = new_value
            _ptr = _ptr->_next;
            return *this; 
        }                         

        friend Iterator operator++(Iterator& it, int unused){  //friend operator: it++
            Iterator temp(it._ptr);
            it._ptr = it._ptr->_next;  
            return temp;
        }
    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    // template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<T>& printMe){
        node<T>* walker = printMe._front;
        while(walker != nullptr){
        outs <<"[" <<  *walker << "]-> ";
        walker = walker -> _next;
        }
        outs << "|||"<< endl;
        return outs;
        }   
    private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T>
Queue<T>::Queue(){
 _front = nullptr;
 _rear = nullptr;
 _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
_size = copyMe._size;
_front = nullptr;
_rear = _copy_list(_front, copyMe._front);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
if(this == &RHS){
    return *this;
}
_clear_list(_front);
_front = nullptr;
_rear = _copy_list(_front, RHS._front);
_size = RHS._size;
return *this;
}

template <typename T>
Queue<T>::~Queue(){
_clear_list(_front);
}

template <typename T>
bool Queue<T>::empty(){
    if(_front == nullptr){
        return true;
    }
    return false;
}

template <typename T>
T Queue<T>::front(){
    return _front->_item;
}

template <typename T>
T Queue<T>::back(){
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item){
    _size++;
// if(_front == nullptr){
//      _front = _insert_head(_front, item);
//      _rear = _front;
// }else{
//node<T>* walker = _rear; 
    node<T>* temp = _insert_after(_front, _rear, item); // [1] -> [2] ->|||
    if(_size == 1){
        _rear = _front;
    }
    else{
        _rear = temp;
    }
}

template <typename T>
T Queue<T>::pop(){
if (_size > 0) {
        _size--;
        if (_size == 0) {
            _rear = NULL;
        }
        else if (_size == 1) {
            _rear = _front;
        }
        return _delete_node(_front, _front);
    }
    return T();
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const{
Iterator it(_front);
return it;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const{
return Iterator();
}


#endif // MYQUQUE_H