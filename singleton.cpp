#include <iostream>
#include <typeinfo>
#include "singleton.hpp"

template<typename T>
T* Singleton<T>::instance = 0;

template<typename T>
T* Singleton<T>::getInstance() {
    if (instance == 0) {
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