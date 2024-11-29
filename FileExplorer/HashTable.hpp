#pragma once

namespace HashTable_n
{
 using  HashFuncation = int (*)(int);

  class HashTable_c
 {
	  typedef struct node
	  {
		  int word;
		  struct node* link;
	  }LishNode;


   private:
	   HashFuncation fun_ = nullptr;
	   LishNode* hash_ = nullptr;
	   int bufsize_;
	   int count1;
	   int count2;
   public:
	   HashTable_c(HashFuncation fun,int bufsize);
	   bool Insert(int word);
	   void PrintHashTable();
	   bool Search(int word);
	   bool Delete(int word);
	   int GetSearchCount();
	   int GetDeleteCount();
	   ~HashTable_c();
 };

}



