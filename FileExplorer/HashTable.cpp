//@todo 模板
#include "HashTable.hpp"
#include <iostream>

namespace HashTable_n
{
	HashTable_c::HashTable_c(HashFuncation fun, int bufsize) :fun_(fun), bufsize_(bufsize) 
	{
		hash_ = new LishNode[bufsize];
		for (int i = 0; i < bufsize_; i++)
		{
			hash_[i].link = nullptr;
		}
	};

	/*
	* @brief  插入关键字
	* @param word 关键字 
	*/
	bool HashTable_c::Insert(int word)
	{
		LishNode* temp = nullptr;
		int location;
		//安全检测
		if (hash_ == nullptr)
		{
			return false;
		}
		location = fun_(word);
		LishNode* node = new LishNode;
		node->word = word;
		node->link = nullptr;
		if (hash_[location].link == nullptr)
			hash_[location].link = node;
		else
		{
			temp = hash_[location].link;
			while (temp->link != nullptr)
			{
				temp = temp->link;
			}
			temp->link = node;
		}
		return true;
	}

	void  HashTable_c::PrintHashTable()
	{
		LishNode* temp = nullptr;
		for (int i = 0; i < bufsize_; i++)
		{    
			std::cout << i<< " ";
			if (hash_[i].link != nullptr)
			{
				temp = hash_[i].link;
				while (temp != nullptr)
				{
					std::cout << temp->word << " ";
					temp = temp->link;
				}
			}
			std::cout << std::endl;
		}
	}

	bool HashTable_c::Delete(int word)
	{
		LishNode* temp = nullptr;
		LishNode* last_temp = nullptr;
		int location = fun_(word);
		{
			if (hash_[location].link != nullptr)
			{
				
				temp = hash_[location].link;
				last_temp = &hash_[location];
				while (temp != nullptr)
				{
					count1++;
					if (temp->word == word)
					{
						last_temp->link = temp->link;
						delete temp;
						return true;
					}
					last_temp = last_temp->link;
					temp = temp->link;
					
				}
				return false;
			}
			else
			{
				return false;
			}
		}
	}

	bool  HashTable_c::Search(int word)
	{
		LishNode* temp = nullptr;
		int location = fun_(word);
		{
			if (hash_[location].link != nullptr)
			{
				count2++;
				temp = hash_[location].link;
				while (temp != nullptr)
				{
					if (temp->word == word)
					{
						return true;
					}
					temp = temp->link;
					
				}
				return false;
			}
			else
			{
				return false;
			}
		}
	}

	int HashTable_c::GetDeleteCount()
	{
		return count1;
	}

	int HashTable_c::GetSearchCount()
	{
		return count2;
	}
}
