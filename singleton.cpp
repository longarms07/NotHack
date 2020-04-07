#include <iostream>
#include <typeinfo>
#include "singleton.hpp"

template<typename T>
T* Singleton<T>::instance = NULL;

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