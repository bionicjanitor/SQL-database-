#ifndef MyStack_H
#define MyStack_H

#include "../queue/MyQueue.h"

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
                                                //  p is pointing to
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

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    
    friend ostream& operator<<(ostream& outs, Stack<T>& printMe){
        node<T>* walker = printMe._top;
        while(walker != nullptr){
        outs <<"[" <<  *walker << "]-> ";
        walker = walker -> _next;
        }
        outs << "|||"<< endl;
        return outs;
    }

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

template <typename T>
Stack<T>::Stack(){
    _top = nullptr;
    _size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe){
    _top = copyMe._top;
    _size = copyMe._size;
}

template <typename T>
Stack<T>::~Stack(){
    _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS){
if(this == &RHS){
    return *this;
}
_clear_list(_top);
_top = _copy_list(RHS._top);
_size = RHS._size;
return *this;
}

template <typename T>                       
T Stack<T>::top(){
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty(){
if(_top == nullptr){
    return true;
 }
   return false; 
}

template <typename T>
void Stack<T>::push(T item){
_size++;
_insert_head(_top, item);
}

template <typename T>
T Stack<T>::pop(){
    _size--;
    return _delete_node(_top, _top);
}

template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const{
Iterator it(_top);
return it;
}

template <class T>
typename Stack<T>::Iterator Stack<T>::end() const{
return Iterator();
}

#endif //MyStack_H