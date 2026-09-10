#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <list>
#include <iostream>

template <class T>

class Sorts{
    private:
        void swap(std::vector<T>&, int, int);
        void copyArray(std::vector<T>&, std::vector<T>&, int, int);
        void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
        void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
        int busqBinariaAux(const std::vector<T>&, const int, const int, const int);
    public:
        std::vector<T> ordenaBurbuja(std::vector<T>&);
        std::vector<T> ordenaSeleccion(std::vector<T>&);
        std::vector<T> ordenaMerge(std::vector<T>&);
        int busqSecuencial(const std::vector<T>&, const int);
        int busqBinaria(const std::vector<T>&, const int);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j){
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T> &v){
    for(int i = v.size()-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(v[j] > v[j+1]){
                swap(v, j, j+1);
            }
        }
    }
    return v;
}

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &v){
    int aux;
    for(int i = 0; i <= v.size()-1; i++){
        aux = i;
        for(int j = i; j <= v.size()-1; j++){
            if(v[j] < v[aux]){
                aux = j;
            }
        }
        if(aux != i){
            swap(v, i, aux);
        }
    }
    return v;
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high){
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;
    while(i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        } else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if(i > mid){
        for(; j <= high; j++){
            B[k++] = A[j];
        }
    } else{
        for(; i <= mid; i++){
            B[k++] = A[i];
        }
    }
}



template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high){
    int mid;
    if((high - low) < 1){
        return;
    }
    mid = low + (high - low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid+1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &v){
    std::vector<T> tmp(v.size());
    mergeSplit(v, tmp, 0, v.size()-1);
    return v;
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &v, const int val){
    int pos = -1;
    for(int i = 0; i <= v.size()-1; i++){
        if(v[i] == val){
            pos = i;
        }
    }
    return pos;
}

template <class T>
int Sorts<T>::busqBinariaAux(const std::vector<T> &v, const int val, const int high, const int low) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    if (v[mid] == val) {
        return mid;
    }
    else if (v[mid] < val) {
        return busqBinariaAux(v, val, high, mid + 1);
    }
    else {
        return busqBinariaAux(v, val, mid - 1, low);
    }
}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &v, const int val){
    int  high, low, pos;
    low = 0;
    high = v.size()-1;
    return busqBinariaAux(v, val, high, low);
}

#endif