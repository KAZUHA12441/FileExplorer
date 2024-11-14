#include "BST.hpp"
#include <iostream>
#include<stdio.h>
namespace  BinaryTree_n
{
	/*
	* @brief BST构造
	*/
	template<class T>
	BST_c<T>::BST_c() :BinaryTree_c<T>() {
		
	};

	/*
	*   @brief BST插入
	*   @param data char或者int 的数据
	*/
	template<class T>
	bool  BST_c<T>::Insert(T  data)
	{

		node<T>* current = this->root_->left_child;
		
		node<T>* parent = nullptr;
		node<T>* ptr = nullptr;

		while (current != nullptr)
		{
			parent = current;
			if (current->data == data)
				return false;
			else if (current->data > data)
				current = current->left_child;
			else if (current->data < data)
				current = current->right_child;
			this->search_count1_++;
		}

		//创建新结点
		ptr = new node<T>; 
		ptr->left_child = nullptr;
		ptr->right_child = nullptr;
		ptr->data = data;

		if (parent == nullptr)
			this->root_->left_child = ptr;
		else if (data > parent->data)
			parent->right_child = ptr;
		else if (data < parent->data)
			parent->left_child = ptr;
		return true;
	}

	 template<class T>
	 bool  BST_c<T>::Search(T data)
	 {
		 node<T>* ptr = nullptr;

		 ptr = this->root_;
		 while (ptr != nullptr)
		 {
			 if (ptr->data == data)
				 return true;
			 else if (ptr->data > data)
				 ptr = ptr->left_child;
			 else if (ptr->data < data)
				 ptr = ptr->right_child;
		 }
		 return false;
	 }

	 template<class T>
	 void  BST_c<T>::GetInsertSearchCount()
	 {
		 std::cout << "插入比较数：" << this->search_count1_ << std::endl;
	 }

	 template<class T>
	 void  BST_c<T>::GetSearchCount()
	 {
		 std::cout <<" 删除比较数：" << this->search_count2_ << std::endl;
	 }

	 template<class T>
	 bool  BST_c<T>::DeleteNode(T  data)
	 {
		 node<T>* ptr = this->root_->left_child;
		 node<T>* last_ptr = nullptr;
		 node<T>* temp = nullptr;
		 node<T>* temp1 = nullptr;
		 node<T>* temp2 = nullptr;
		 int i = 0;
 		 while (ptr != nullptr)
		 {
			 if (ptr->data == data)
				 break; 
			 last_ptr = ptr;
			 if (ptr->data > data)
				 ptr = ptr->left_child;
			 else if (ptr->data < data)
				 ptr = ptr->right_child;
			 this->search_count2_++;
		 }
		 if (ptr->left_child == nullptr && ptr->right_child == nullptr)
		 {
			 if (last_ptr->left_child != nullptr)
			 {
				 if (last_ptr->left_child->data == data)
				 {
					 last_ptr->left_child = nullptr;
				 }
			  }
			 if (last_ptr->right_child != nullptr)
				 {
					 if (last_ptr->right_child->data == data)
					 {
						 last_ptr->right_child = nullptr;
					 }
				 }
		 }
		 else if (ptr->left_child == nullptr && ptr->right_child != nullptr)
		 {
			 if (last_ptr != nullptr)
			 {
				 if (last_ptr->left_child != nullptr)
			 {
				 if (last_ptr->left_child->data == data)
				 {
					 last_ptr->left_child = ptr->right_child;
				 }
			 }
			 if (last_ptr->right_child != nullptr)
			 {
				 if (last_ptr->right_child->data == data)
				 {
					 last_ptr->right_child = ptr->right_child;
				 }
			 }
			 }
			 else
			 {
				 this->root_->left_child = ptr->right_child;
			 }
		 }
		 else if (ptr->left_child != nullptr && ptr->right_child == nullptr)
		 {
			 if (last_ptr != nullptr)
			 {
				 if (last_ptr->left_child != nullptr)
				 {
					 if (last_ptr->left_child->data == data)
					 {
						 last_ptr->left_child = ptr->left_child;
					 }
				 }
				 if (last_ptr->right_child != nullptr)
				 {
					 if (last_ptr->right_child->data == data)
					 {
						 last_ptr->right_child = ptr->left_child;
					 }
				 }
			 }
			 else
			 {
				 this->root_->left_child = ptr->left_child;
			 }
		 }
		 else if (ptr->left_child != nullptr && ptr->right_child != nullptr)
		 {
			 temp = ptr->left_child;
			 if (last_ptr != nullptr)
			 {
				 if ((temp->left_child != nullptr && temp->right_child == nullptr) || (temp->left_child == nullptr && temp->right_child == nullptr))
				 {
					 if (last_ptr->left_child != nullptr)
					 {
						 if (last_ptr->left_child->data == data)
						 {
							 temp->right_child = ptr->right_child;
							 last_ptr->left_child = temp;
						 }
					 }
					 if (last_ptr->right_child != nullptr)
					 {
						 if (last_ptr->right_child->data == data)
						 {
							 temp->right_child = ptr->right_child;
							 last_ptr->right_child = temp;
						 }
					 }
				 }
				 else
				 {
					 while (1)
					 {
						 if (temp->right_child == nullptr && temp->left_child == nullptr)
						 {
							 temp1->right_child = nullptr;
							 break;
						 }
						 temp1 = temp;
						 temp = temp->right_child;
					 }
					 if (last_ptr->left_child != nullptr)
					 {
						 if (last_ptr->left_child->data == data)
						 {
							 last_ptr->left_child = temp;
							 temp->left_child = ptr->left_child;
							 temp->right_child = ptr->right_child;
						 }
					 }
					 if (last_ptr->right_child != nullptr)
					 {
						 if (last_ptr->right_child->data == data)
						 {
							 last_ptr->right_child = temp;
							 temp->left_child = ptr->left_child;
							 temp->right_child = ptr->right_child;
						 }
					 }
				 }
			 }
			 else
			 {
				 while (1)
				 {
					 if (temp->right_child == nullptr && temp->left_child == nullptr)
					 {
						 temp1->right_child = nullptr;
                       break;
					 }
					 temp1 = temp;
					 temp = temp->right_child;
				 }
				 this->root_->left_child = temp;
				 temp->left_child = ptr->left_child;
				 temp->right_child = ptr->right_child;
			 }
		 }

		 delete ptr;
		 return false;
	 }
}