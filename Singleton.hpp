#pragma once

/*****************
 TODO:
  - Prevent race conditions on instance
******************/

template<typename T>
class Singleton {
    private:
        static T* instance;

    public:
        static T* getInstance();

    protected:
        Singleton();

    private:
        void* operator new(size_t);
};