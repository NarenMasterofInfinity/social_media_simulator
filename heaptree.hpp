#include "classes.hpp"


#ifndef HEAP_H
#define HEAP_H 
template <typename T>
void HeapTree<T>::swap(T *x, T *y){
    T temp = *x;
    *x = *y;
    *y = temp;
}

template <typename T>
int HeapTree<T>::left(int i){
    return 2*i+1;
}

template <typename T>
int HeapTree<T>::right(int i){
    return left(i) + 1;
}

template <typename T>
int HeapTree<T>::parent(int i){
    return (i-1)/2;
}

template <typename T>
T HeapTree<T>::extract_max(vector<T> &cp){
    T max = cp[0];
    int n = cp.size();
    swap(&cp[0], &cp[n-1]);
    cp.pop_back();
    heapify(0,cp);
    
    return max;
}

template <typename T>
void HeapTree<T>::insert(T val){
    arr.push_back(val);
    int n = arr.size();
    int p = parent(n-1);
    int i = n-1;
    while(p >=0 && arr[p] < arr[i]){
        swap(&arr[p],&arr[i]);
        i = p;
        p = parent(i);
    }
}

template <typename T>
void HeapTree<T>::delete_node(T val){
    int i;
    int n = (int) arr.size();
    for(i = 0; i < n; i++){
        if (arr[i] == val){
            break;
        }
    }
    swap(&arr[i], &arr[n-1]);
    arr.pop_back();


    for(int j = (arr.size()-1)/2; j >= 0; j--){
        heapify(j,arr);
    }
}

template <typename T>
T HeapTree<T>::search(int i){
    copy = arr;
    int j = 1;
    while(copy.size() != 0){
        T val = extract_max(copy);
        if(j == i){
            //this->delete_node(val);
            return val;
        }
        j++;
    }
    return extract_max(copy);
}

template <typename T>
void HeapTree<T>::heapify(int i, vector<T>& arr){
        int largest = i;
        int l = left(i);
        int r = right(i);
        if(l < arr.size() && arr[l] > arr[largest]){
            largest = l;
        }
        if(r < arr.size() && arr[r] > arr[largest]){
            largest = r;
        }
        if(largest != i){
            swap(&arr[largest], &arr[i]);
            heapify(largest, arr);
        }
}

template<typename T>
void HeapTree<T> :: delete_element(int i){
    copy = arr;
    int j = 1;
    while(copy.size() != 0){
        T val = extract_max(copy);
        if(j == i){
            this->delete_node(val);
            return;
        }
        j++;
    }
}
template <typename T>
void HeapTree<T>::sorted_display(){
    copy = arr;
    int size = copy.size();
    int i = 0;
    while(!copy.empty()){
        cout << ++i << " ." ;
        extract_max(copy).display();
    }
}

#endif