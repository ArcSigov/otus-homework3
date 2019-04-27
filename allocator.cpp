#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <array>
#include <list>
#include "local_allocator.h"
#include "container.h"






int main(int, char *[]) {
    //  auto v = std::vector<int, logging_allocator<10,int>>{};
    //  //v.reserve(10);
    //  for (size_t i = 0; i < 8 /* 5 */; ++i) {
    //      v.push_back(i);
    //      std::cout << std::endl;
    //  }
    // std::cout << std::endl;
    // for (auto i: v) {
    //     std::cout << i << std::endl;
    // }

   auto m = std::map<int, int, std::less<int>, logging_allocator<10,std::pair<const int, int>>>{};
    for (size_t i = 0; i < 10; ++i) {
       m[i] = i;
   }
    for (auto i = 0 ; i < 10 ; i++)
    {
        std::cout << m[i];
    }
    std::cout << std::endl;


    easy_forward_list<int,logging_allocator<10,int>> var;
    for (auto i = 0 ; i < 10 ; i++){
         var.emplace_back(i);
    }

      for (auto i = 0; i<var.size();i++)
      {
          std::cout<<var[i];
      }
    return 0;
}