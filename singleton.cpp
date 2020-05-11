#include <iostream>
#include <typeinfo>
#include "singleton.hpp"

/**********************
 * Implementation of Singleton pattern
 **********************/

template<typename T>
T* Singleton<T>::instance = NULL;

/**********************
 * If an instance has not been created,
 * create it.
 * Return the instance.
 **********************/
template<typename T>
T* Singleton<T>::getInstance() {
    if (instance == NULL) {
        instance = new T();
    }
    
    return instance;
}

template<typename T>
void* Singleton<T>::operator new(size_t size) {
    return malloc(size);
}

template<typename T>
Singleton<T>::Singleton() { }