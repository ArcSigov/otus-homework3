#pragma once 

#include <iostream>
#include <memory>
#include <array>


//Класс выделения памяти (делает резерв памяти и при вызове метода allocate берет пул уже отсюда)
template<typename T,std::size_t size>
class memory_pool
{
    
public:
     memory_pool(std::size_t __size = std::size_t());
     ~memory_pool();
     T* get();
     T* resize(std::size_t n);
     void free(T* val, std::size_t n);
private:
    unsigned long iterator;
    std::size_t real_size;
    std::array<T*,10> pool = {0};         //!< массив указателей с шагом размера типа объекта
    void alarm()
    {
        throw std::bad_alloc();
    }
};


template<typename T,std::size_t size>
memory_pool<T,size>::memory_pool(std::size_t __size) : real_size(__size)
{
    std::cout<< "real_size=" << real_size;
    iterator = 0;
    for (unsigned long i = 0 ; i < 10 ; i++)
    {
        pool[i] = nullptr;
    }
}

template<typename T,std::size_t size>
memory_pool<T,size>::~memory_pool()
{
    std::cout << __PRETTY_FUNCTION__;
    if(pool[0])
    std::free(pool[0]);
    std::cout << "free";
}


template<typename T,std::size_t size>
T* memory_pool<T,size>::get()
{
    pool[0] = reinterpret_cast<T*>(std::malloc(real_size * sizeof(T*)));
    if (!pool[0])
        alarm();

    auto p1 = pool[0];
    for (unsigned long i = 1 ; i < real_size; ++i)
    {
        p1 +=sizeof(T*);
        pool[i] = p1;
    }
    iterator = 1;
    return pool[0];
}

template<typename T,std::size_t size>
T* memory_pool<T,size>::resize(std::size_t n)
 //!< Сдвигает указатель под объект, если данный запрашивал еще память под элементы 
{
    iterator +=n;
    std::cout << iterator << std::endl;
    if (iterator > real_size)
            alarm();
        return pool[iterator-n];
}



template<typename T,std::size_t size>
void memory_pool<T,size>::free(T* val, std::size_t n)
{
    //!< удерживаем память
    for (unsigned long i = 0 ; i < real_size ; ++i)
    {
        if (val == pool[i])
        {
            iterator = i;
            return;
        }
    }
    std::free(pool[0]);
}