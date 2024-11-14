#pragma once
#ifndef  __BST_HPP
#define __BST_HPP

#include "BinaryTree.hpp"

namespace BinaryTree_n
{
  template<class T> class BST_c: public BinaryTree_c<T>
  {
    private:
        int  search_count1_ = 0;
        int  search_count2_ = 0;
    public :
         BST_c();
         
         bool  Insert(T data); 
         bool  Search(T  data);
         bool  DeleteNode(T  data);
         void  GetInsertSearchCount();
         void  GetSearchCount();
  };



};

#endif /*__BST_HPP*/

