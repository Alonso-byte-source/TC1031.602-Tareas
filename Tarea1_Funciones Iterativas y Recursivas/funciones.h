/*
 * funciones.h
 *
 *  Created on: 18/08/2026
 *      Author: Alonso Vega Reséndiz
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H

#include <iostream>

class Funciones{
    public:
        Funciones();
        long sumaIterativa(int);
        long sumaRecursiva(int);
        long sumaDirecta(int);
};

Funciones::Funciones(){};

long Funciones::sumaIterativa(int n){
    long accum = 0;
    for(int i = 1; i <= n; i++){
        accum += i;
    }
    return accum;
}

long Funciones::sumaRecursiva(int n){
    if(n < 0) return 0;
    else return (n + sumaRecursiva(n-1));  
}

long Funciones::sumaDirecta(int n){
    int res;
    res = (n * (n + 1)) / 2;
    return res;

}

#endif