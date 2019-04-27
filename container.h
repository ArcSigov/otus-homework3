#pragma once

#include <iostream>
#include <memory>
#include "local_allocator.h"


template<typename T, typename Allocator = std::allocator<T>>
class easy_forward_list
{
    using val_type = T;
    using pval_type = T*;
    using rval_type = T&;
    using crval_type = const T&;

public:

    explicit easy_forward_list(Allocator _allocator = Allocator()): allocator(_allocator){nodes_counter =0,node = nullptr;};
    easy_forward_list(std::initializer_list<T> list, Allocator _allocator = Allocator());
    ~easy_forward_list();


    void emplace_back(crval_type data);
    int size(){return nodes_counter;};
    T& operator[](const int pos);
    
private:
    template<typename U>
    class Node
    {
      public:
        U data;
        Node* next;
        Node (U data = U(),Node* next = nullptr){
            this->data = data;
            this->next = next;
        };
    };
    using rebinded = typename std::allocator_traits<Allocator>::template rebind_alloc<Node<T>>;
    Allocator allocator;
    rebinded r_allocator;
    std::initializer_list<T> list;
    void allocator_operates(const T& data);
    Node<T> * node;
    int nodes_counter;
    

};

template<typename T, typename Allocator>
easy_forward_list<T,Allocator>::easy_forward_list(std::initializer_list<T> _list, Allocator _allocator):
    allocator(_allocator),
    list(_list)
{ 
        nodes_counter =0;
        node = nullptr;  
        //!< Аллоцируем память под загрузочный лист ( знание, что аллокатор ограничен 10тью будет обработано не в этом классе, потому нет смысла вызывать исключение
        for (auto it:list)
        {
            allocator_operates(it);
        }
};

template<typename T, typename Allocator>
easy_forward_list<T,Allocator>::~easy_forward_list(){
    
    Node<T> *current = this->node;

    while (nullptr != current)
     {
         allocator.destroy(current);
         r_allocator.deallocate(current,1);
         current = current->next;
     }

};



template<typename T, typename Allocator>
void easy_forward_list<T,Allocator>::allocator_operates(crval_type data)
{
     auto allocated =  r_allocator.allocate(1);
     allocator.construct(allocated,Node<T>(data));

     if (node == nullptr)
     {
        node = allocated;//!< первый
     }
     else
     {
         auto current = this->node;
         while ( current->next != nullptr)
         {
             current = current->next;
         }
         current->next = allocated;
     }
     nodes_counter++;
};

template<typename T, typename Allocator>
void easy_forward_list<T,Allocator>::emplace_back(crval_type data)
{
    allocator_operates(data);
};

template<typename T, typename Allocator>
T& easy_forward_list<T,Allocator>::operator[](const int pos)
{
    auto current = this->node;
    auto counter = 0;
    
    while (current != nullptr)
    {
        if (pos ==counter)
            return current->data;
        current = current->next;
        counter++;
    }
}