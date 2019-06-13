#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <array>

#include "local_allocator.h"
#include "container.h"


static const int v_size = 10;

unsigned int factorial (unsigned int x)
{
    if( x == 0 ) return 1;
    return x * factorial (x - 1);
}

int main(int, char *[])
{

    auto map_cast_alloc = std::map<int, int> {};
    for (auto i = 0; i < v_size; ++i)
    {
        map_cast_alloc[i] = factorial(i);
        std::cout << i << " " <<  map_cast_alloc[i] << std::endl;
    }
    std::cout << std::endl;

    auto map_user_alloc = std::map<int, int, std::less<int>,logging_allocator<v_size,std::pair<const int, int>>> {};
    for (size_t i = 0; i < v_size; ++i)
    {
        map_user_alloc[i] = factorial(i);
        std::cout << i << " " <<  map_user_alloc[i] << std::endl;
    }
    std::cout << std::endl;


    auto list_cast_alloc = easy_forward_list<int> {};
    for (auto i = 0 ; i < v_size ; i++)
    {
        list_cast_alloc.emplace_back(i);
        std::cout<<list_cast_alloc[i] << " ";
    }
    std::cout << std::endl;

    auto list_user_alloc = easy_forward_list<int,logging_allocator<v_size,int>> {};
    for (auto i = 0 ; i < v_size; i++)
    {
        list_user_alloc.emplace_back(i);
        std::cout<<list_user_alloc[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
