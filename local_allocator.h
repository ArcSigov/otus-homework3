#pragma once

#include <iostream>
#include <memory>
#include "local_memory.h"


template<std::size_t res_size,typename T>
struct logging_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;


    
    template<typename U>
    struct rebind {
        using other = logging_allocator<res_size,U>;
    };


    T *allocate(std::size_t n) 
    {
          if (n>res_size)
               throw std::bad_alloc();
         if (0 == called){
            called = 1;
            return memory.get();
         }
        
        return  memory.resize(n);
    }


    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }

    void deallocate(T *p, std::size_t n) {
        if (0 == is_free)
        {
            memory.free(p,n);
            is_free = 1;
        }
    }


private:
    int is_free = 0;
    int called =0;
    memory_pool<value_type,res_size> memory;
};
