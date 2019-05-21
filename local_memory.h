#pragma once

#include <iostream>
#include <memory>
#include <array>


template<typename T,int size>
class memory_pool
{

public:
    memory_pool();
    ~memory_pool();
    T* get();
    T* resize(std::size_t n);
    void free(T* val, std::size_t n);
private:
    unsigned long iterator;
    std::array< T*, size > pool;
    void alarm()
    {
        throw std::bad_alloc();
    }
};


template<typename T,int size>
memory_pool<T,size>::memory_pool()
{
    for (unsigned long i = 0 ; i < size ; i++)
    {
        pool[i] = nullptr;
    }
}

template<typename T,int size>
memory_pool<T,size>::~memory_pool()
{
    if(pool[0])
        std::free(pool[0]);
}


template<typename T,int size>
T* memory_pool<T,size>::get()
{
    auto aaa = reinterpret_cast<T*>(std::malloc(size * sizeof(T)));
    if (!aaa) alarm();

    for (unsigned long i = 0 ; i < size; ++i)
    {
        pool[i] = aaa;
        aaa++;
    }
    iterator = 1;
    return pool[0];
}

template<typename T,int size>
T* memory_pool<T,size>::resize(std::size_t n)
{
    iterator +=n;
    if (iterator == size+1)
        alarm();
    return pool[iterator-n];
}

template<typename T,int size>
void memory_pool<T,size>::free(T* val, std::size_t n)
{
   auto counter_calls = 0;
   auto valid = 0;

   if (val == pool[0]) {valid = 1;}

   if (counter_calls == size && valid)
   {
       std::free(pool[0]);
   }
   counter_calls++;
}
