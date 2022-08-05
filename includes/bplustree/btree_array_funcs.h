
#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

using namespace std;

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

template <class T>
T maximal(const T& a, const T& b){
    if(a < b){
        return a;
    }
    return b;
}
 

template <class T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){
    n = 0;
    T temp = data[0];
    int max_index;
    for(int i = 0; i < n; i++){
        if(data[i] > temp){
            temp = data[i];
            max_index = i;
        }
    }
    return max_index;
}


template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    for(int i = 0; i < n; i++){
        if(entry <= data[i]){
            insert_item(data, i, n, entry);
        }
    }
    
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    for(int i = 0; i < n; i++){
        if(data[i] >= entry){
            return i;
        }
    }
    return n;
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    n++;
    data[n-1] = entry;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){   
    //T temp = data[i]; 
    for(int j = n; j > i; j--){
        data[j] = data[j-1];
    }
    data[i] = entry;  
    n++;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){
    if(n == 0){
        //cout << "empty data array.." << endl;
        return;
    }
    entry = data[n - 1];
    n--;
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    if(n == 0){
        entry = data[i];
        return;
    }
    entry = data[i];
    for(int j = i; j+1 < n; j++){
        data[j] = data[j+1];
    }
    n--;
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    int n3 = n1 + n2;
    int count = 0;
    for(int i = n1; i < n3; i++){
        data1[i] = data2[count];
        count++;
    }
    n1 = n3;
    n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    n2 = n1/2;
    n1 = n1 - n2;
    for(int i = 0; i < n2; i++){
        data2[i] = data1[i+n1];        
    }
}



template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){
    int count = 0;
    for(int i = 0; i < src_size; i++){
        dest[i] = src[i]; 
        count++;
    }
    dest_size = src_size;
}


template <class T>
void print_array(const T data[], int n, int pos){
    for(int i = 0; i < n; i++){
        cout << "[" << data[i] << "]";
    }
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    for(int i =0; i < n; i++){
        if(item < data[i]){
            return false;
        }
    }

    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    for(int i =0; i < n; i++){
        if(item > data[i]){
            return false;
        }
    }


    return true;
}



template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    list.push_back(addme);
    return list; 
}

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    for(int i = 0; i < list.size(); i++){
        outs << list[i] << "| " ;
    }
    
    return outs;
}




#endif