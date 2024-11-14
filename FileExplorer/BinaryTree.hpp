	
#ifndef __BINARYTREE_HPP
#define __BINARYTREE_HPP

namespace BinaryTree_n
{
    template<class T> struct node
	{
		T data;
		node<T>* left_child;
		node<T>* right_child;
	};

	template<class T> class BinaryTree_c
	{
	    private:
        static void  PreOrder(node<T>* root);
		static void  PostOrder(node<T>* root);
		static void  InOrder(node<T>* root);
		static void  Destroy(node<T>* root);
		protected:
			node<T>* root_;
			int node_count_; 
			int tree_high_;
	    public:
			BinaryTree_c();
            
			//二叉树操作
			node<T>* InsertLeftNode(node<T>* tree_node, T const& data);
			node<T>* InsertRightNode(node<T>* tree_node, T const& data);
			node<T>* DeleteLeftTree(node<T>* curr);
			node<T>* DeleteRightTree(node<T>* curr);
			
			//二叉树遍历
			void  PreOrder();
			void  PostOrder();
			void  InOrder();
			void  Destroy();
		
			node<T>* Search(node<T>* root, T const& data);
			
			node<T>  *GetTreeRoot();

			~BinaryTree_c();
	};
}




#endif /*__BINARYTREE_HPP*/