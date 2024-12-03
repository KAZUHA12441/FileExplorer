#include "BinaryTree.hpp"
#include <iostream>
#include <new>


namespace BinaryTree_n
{
	template <class T>
	BinaryTree_c<T>::BinaryTree_c():node_count_(0), tree_high_(0)
	{
		root_ = new  node<T>;
		root_->data = NULL;
		root_->left_child = nullptr;
		root_->right_child = nullptr;
	}

	/*
	* @brief 插入某结点的左孩子
	* @param tree_node  插入的结点
	* @param data 数据
	*/
	template <class T>
	node<T>* BinaryTree_c<T>::InsertLeftNode(node<T>* tree_node, T const& data)
	{
		node<T>* new_node = new node<T>;
		new_node->data = data;
		new_node->left_child = nullptr;
		new_node->right_child = nullptr;
		if (tree_node->left_child == nullptr)
		{
			tree_node->left_child = new_node; 
		}
		else
		{
			new_node->left_child = tree_node->left_child;
			tree_node->left_child = new_node;
		}
		return  tree_node->left_child;
	}

	/*
	* @brief 插入某结点的右孩子
	* @param tree_node  插入的结点
	* @param data 数据
	*/
	template <class T>
	node<T>* BinaryTree_c<T>::InsertRightNode(node<T>* tree_node, T const& data)
	{
		node<T>* new_node = new node<T>;
		new_node->data = data;
		new_node->right_child = nullptr;
		new_node->right_child = nullptr;
		if (tree_node->right_child == nullptr)
		{
			tree_node->right_child = new_node;
		}
		else
		{
			new_node->right_child = tree_node->right_child;
			tree_node->right_child = new_node;
		}
		return  tree_node->right_child;
	}

	/*
	* @brief  删除左子树
	* @param curr 结点指针
	*/
	template <class T>
	node<T>* BinaryTree_c<T>::DeleteLeftTree(node<T>* curr)
	{
		if (curr->left_child == nullptr || curr == nullptr)
		{
			return nullptr;
		}
		if (Destroy(curr->left_child))//删除右子树
		{
			return curr;
		}
		return nullptr;
	}
	

	/*
	* @brief  删除右子树
	* @param curr 结点指针
	*/
	template <class T>
	node<T>* BinaryTree_c<T>::DeleteRightTree(node<T>* curr)
	{
		if (curr->right_child == nullptr || curr == nullptr)
		{
			return nullptr;
		}	
		if (Destroy(curr->right_child))//删除右子树
		{
			return curr;
		}
		return nullptr;
	}
    
	/*
	* @brief  前序遍历 
	*/
	template <class T>
	void  BinaryTree_c<T>::PreOrder()
	{
		PreOrder(root_);
	}

	/*
	* @brief  前序遍历(无法外部调用)
	*/
	template <class T>
	 void  BinaryTree_c<T>::PreOrder(node<T>* root)
	{
		 if (root != nullptr)
		 {
			 std::cout << root->data << std::endl;
			 PreOrder(root->left_child);
			 PreOrder(root->right_child);
		 }
	}

	 /*
	 * @brief  中序遍历
	 */
	 template <class T>
	 void  BinaryTree_c<T>::InOrder()
	 {
		 InOrder(root_->left_child);
	 }

	 /*
	 * @brief  中序遍历(无法外部调用)
	 */
	 template <class T>
	 void  BinaryTree_c<T>::InOrder(node<T>* root)
	 {
		 if (root != nullptr)
		 {
			 InOrder(root->left_child); 
			 std::cout << root->data<<" ";
			 InOrder(root->right_child);
		 }
	 }

	 /*
	* @brief  后序遍历
	*/
	 template <class T>
	 void  BinaryTree_c<T>::PostOrder()
	 {
		 PostOrder(root_);
	 }

	 /*
	 * @brief  后序遍历(无法外部调用)
	 */
	 template <class T>
	 void  BinaryTree_c<T>::PostOrder(node<T>* root)
	 {
		 if (root != nullptr)
		 {
			 PostOrder(root->left_child);
			 PostOrder(root->right_child);
			 std::cout << root->data << std::endl;
		 }
	 }

	 template <class T>
	 void  BinaryTree_c<T>::Destroy()
	 {
		 Destroy(root_);
	 }

	 /*
	 * @brief 删除整颗树
	 *  @param  root 根结点
	 */
	 template <class T>
	 void  BinaryTree_c<T>::Destroy(node<T>* root)
	 {
		 if (root != nullptr && root->left_child != nullptr)
		 {
			 Destroy(root->left_child);
		 }
		 else if (root != nullptr && root->right_child != nullptr)
		 {
			 Destroy(root->right_child);
		 }
		 delete root;
	 }

	 /*
	 * @brief 查找一个结点 
	 * @param root 根
	 * @param data  查找的数据
	 */
	 template <class T>
	 node<T>* BinaryTree_c<T>::Search(node<T>* root, T const& data)
	 {
		 node<T>* find = nullptr;
		 if (root != nullptr)
		 {
			 if (root->data == data)
			 {
				 find = root;
			 }
			 else
			 {
				 find = Search(root->left_child, data);
				 if (find == nullptr)
				 {
					 find = Search(root->right_child, data);
				 }
			 }
		 }
		 return find; 
	 }

	 /*
	 * @brief 获取树的根
	 * @param  无
	 */
	 template <class T>
	 node<T>* BinaryTree_c<T>::GetTreeRoot()
	 {
		 return root_;
	 }

	 /*
	 * @brief 析构函数
	 */
	 template <class T>
	 BinaryTree_c<T>::~BinaryTree_c()
	 {
		 Destroy(root_);
	 }

	 template<class T>
	 void BinaryTree_c<T>::LeftOrder(node<T>* root)
	 {
		 if (root != nullptr)
		 {
			 RightOrder(root->left_child);
			 std::cout << root->data << std::endl;
		 }
	 }
	 template<class T>
	 void BinaryTree_c<T>::RightOrder(node<T>* root)
	 {
		 if (root != nullptr)
		 {
			 RightOrder(root->right_child);
			 std::cout << root->data << std::endl;
		 }
	 }
}