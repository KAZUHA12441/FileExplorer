#include "Explorer.hpp"
#include <iostream>
#include <fstream>

namespace Explorer_n
{
	std::vector< std::string>  command_Group = {"/help 查看命令", 
		                                                                      "/readAttributes 查看属性",
		                                                                      "/readTree 查看文件树",
		                                                                      "/readAdd 查看当前地址",
	                                                                          "/goBack 回到上一层",
	                                                                          "/goInto 进入下一层",
	                                                                          "/createFile 在当期目录下创建一个文件",
	                                                                          "/deleteFile 删除当前目录下的一个文件",
	                                                                          "/createFolder 在当前目录下创建一个文件夹",
	                                                                          "/deleteFolder 删除当前目录下的一个文件夹",
		                                                                      "/Rename 对文件或者文件夹进行重命名"
	                                                                          "/search 查找路径",
	                                                                          "/exit 结束程序"};
	Explorer::Explorer()
	{
		mydisk = Disk_n::Disk_c::myDisk;
		mydisk->CreatePartition("C:", 1024, Disk_n::LOCAL, Disk_n::NTFS);
		mydisk->CreatePartition("D:", 2048, Disk_n::LOCAL, Disk_n::NTFS);
		data = new InputData_s;
	}

	int Explorer::GetCommand()
	{ 
		std::string  temp;
		std::string mess;
		size_t i = 0;
		size_t j = 0;
		std::cin >> data->command;
		if (data->command.at(0) == '/')
		{
			i = data->command.find_first_of('/');
		    temp = data->command.substr(i + 1);
			system("cls");
			if (temp == "help") 
			{
				Help();
			}
			else if (temp == "Mouse")
			{
				GetInputName();
				Mouse();
			}
			else if (temp == "readAttributes")
			{
				ReadAttributes();
			}
			else if (temp == ":readTree")
			{
				ReadTree();
			}
			else if (temp == "readAdd")
			{
				ReadAdd();
			}
			else if (temp == "goBack")
			{
				GoBack();
			}
			else if (temp == "goInto")
			{
				GetInputName();
				GoInto(data->name);
			}
			else if (temp == "createFile")
			{
				GetInputName();
				GetInputSize();
				GetInputOwner();
				GetInputCommand();
				CreateFile();
			}
			else if (temp == "deleteFile")
			{
				GetInputName();
				DeleteFile();
			}
			else if (temp == "createFolder")
			{
				GetInputName();
				CreateFolder();
			}
			else if (temp == "deleteFolder")
			{
				GetInputName();
				DeleteFolder();
			}
			else if (temp == "search")
			{
				GetInputName();
				Search(data->name);
			}
			else if (temp == "exit")
			{
				Exit();
			}
			else
			{
				std::cout << "错误的命令" << "输入help查询所有命令" << std::endl;
			}
		}
		else
		{
			std::cout << "格式错误" << std::endl;
		}

		return 0;
	}

	/*
	*  @brief  命令列表
	*/
	void Explorer::Help()
	{
		for (std::string  temp : command_Group)
		{
			std::cout << temp << std::endl;
		}
	}


	/*
	* @brief 查看文件属性
	*/
	void Explorer::ReadAttributes()
	{
		if (!add.empty())
		{
          if (now->data->Type == true)
		 {
			  now->data->File->GetAttributes();
		 }
		 else if(now->data->Type == false)
		 {
			  now->data->Folder->GetAttributes();
		 }
		}
	}

	/*
	* @查看文件树
	*/
	void Explorer::ReadTree()
	{


	}

	/*
	* @brief 查看文件地址
	 */
	std::string Explorer::ReadAdd()
	{
		return now->data->Folder->GetAddress();
	}

	void Explorer::GoBack()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* nodetemp = nullptr;
		add.pop();
		if (add.empty())
		{
			return;
		}
		nodetemp = add.top();
		now = nodetemp;
		
		
	}
	
	/*
	* @brief  进入一个文件夹
	* @param  temp 需进入的文件夹
	*/
	void Explorer::GoInto(std::string temp)
	{
		BinaryTree_n::node<Disk_n::Key_s*>*nodetemp = nullptr;
		if (add.empty())
		{
			now_disk =  mydisk->GetPartition(temp);
			if (now_disk == nullptr)
			{
				return;
			}
			now = now_disk->root_->GetTreeRoot();
			now->data = new  Disk_n::Key_s; 
			now->data->Folder = new File_n::Folder_c(now_disk->name);
			now->data->Folder->SetAddress(now_disk->name);
			add.push(now);
		}
		else
		{
			    nodetemp = root_search(now->left_child, temp);
				if (nodetemp != nullptr)
				{	
					now = nodetemp;
					add.push(now);
					
				}
				else
				{
					std::cout << "无此文件夹" << std::endl;
				}
		}
	}

	/*
	* @brief  创建文件
	*/
	void Explorer::CreateFile()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1 = now->left_child;

		Disk_n::Key_s* mykey = new Disk_n::Key_s;
		mykey->Type = true;
		mykey->File = new File_n::File_c(data->owner,data->name, data->size,data->file_type); 

		BinaryTree_n::node<Disk_n::Key_s*>* temp2 = new BinaryTree_n::node<Disk_n::Key_s*>;
		temp2->data = mykey;
		temp2->left_child = nullptr;
		temp2->right_child = nullptr;
		now->data->Folder->createFile();
		if (!add.empty())
		{
			if (temp1 == nullptr)
			{
				temp2->data->File->SetAddress(now->data->Folder->name_ +"\\"+ mykey->File->name_+'.'+ mykey->File->file_type);
				now->left_child = temp2;
				return;
			}
			while (1)
			{
				if (temp1->right_child == nullptr)
				{
					break;
				}
				temp1 = temp1->right_child;
			}
			temp2->data->File->SetAddress(now->data->Folder->name_ + "\\" + mykey->File->name_ + '.' + mykey->File->file_type);
			temp1->right_child = temp2;
		}
	}

	/*
	* @brief 删除某个文件
	* @name 需要删除的文件
	*/
	void Explorer::DeleteFile()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1;
		BinaryTree_n::node<Disk_n::Key_s*>* temp2;
		now->data->Folder->deleteFile();
		if (now->left_child != nullptr)
		{
			if (now->left_child->data->Type == true)
			{
				if (now->left_child->data->File->name_ == data->name) 
				{
					temp1= now->left_child;
					now->left_child = now->left_child->right_child;
					return;
				}
			}
			temp1 = now->left_child;
			while (1)
			{
				if (temp1 == nullptr)
				{
					std::cout << "找不到此文件" << std::endl;
					break;
				}
				if (temp1->data->File->name_ == data->name)
				{
					temp2->right_child = temp1->right_child;
					delete temp1;
					break;
				}
				temp2 = temp1;
				temp1 = temp1->right_child;
				
			}
	   }
		else
		{
			std::cout << "找不到文件" << std::endl;
		}
	}

	/*
	* @brief  创建一个文件夹
	* @param 创建文件夹名
	*/
	void Explorer::CreateFolder()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1 = now->left_child;

		Disk_n::Key_s* mykey = new Disk_n::Key_s;
		mykey->Type = false;
		mykey->Folder = new File_n::Folder_c(data->name);

		BinaryTree_n::node<Disk_n::Key_s*>* temp2 = new BinaryTree_n::node<Disk_n::Key_s*>;
		temp2->data = mykey;
		temp2->left_child = nullptr;
		temp2->right_child = nullptr;
		now->data->Folder->createFolder();
		if (!add.empty())
		{
			if (temp1 == nullptr)
			{
				temp2->data->Folder->SetAddress(now->data->Folder->name_ + "\\" + mykey->Folder->name_);
				now->left_child = temp2;
				return;
			}
			while (1)
			{
				if (temp1->right_child == nullptr)
				{
					break;
				}
				temp1 = temp1->right_child;
			}
			temp2->data->Folder ->SetAddress(now->data->Folder->name_ + "\\" + mykey->Folder->name_);
			temp1->right_child = temp2;
		}
	}

	/*
	* @brief 删除一个文件夹
	* @param 删除文件夹的名字
	*/
	void Explorer::DeleteFolder()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1;
		BinaryTree_n::node<Disk_n::Key_s*>* temp2;
		now->data->Folder->deleteFolder();
		if (now->left_child != nullptr)
		{
			if (now->left_child->data->Type == true)
			{
				if (now->left_child->data->File->name_ == data->name)
				{
					temp1 = now->left_child;
					now->left_child = now->left_child->right_child;
					return;
				}
			}
			temp1 = now->left_child;
			while (1)
			{
				if (temp1 == nullptr)
				{
					std::cout << "找不到此文件" << std::endl;
					break;
				}
				if (temp1->data->Folder->name_ == data->name)
				{
					temp2->right_child = temp1->right_child;
					while (1)
					{

					}
					delete temp1;
					break;
				}
				temp2 = temp1;
				temp1 = temp1->right_child;

			}
		}
		else
		{
			std::cout << "找不到文件" << std::endl;
		}
	}

	void Explorer::Rename(std::string name)
	{
		if (mouse->data->Type == true)
		{
			mouse->data->File->Rename(name);
		}
		else {
			mouse->data->Folder->Rename(name);
		}
	}

	void Explorer::Search(std::string name)
	{
		root_search(now->left_child,name);
	}

	void  Explorer::Exit()
	{
		exit(EXIT_SUCCESS);
	}


	/*
	* @brief 鼠标/游标?
	*/
	void  Explorer::Mouse()
	{
		mouse = root_search(now, data->name);
	}
	





	/*
	* @brief 显示函数
	*/
	void Explorer::Show()
	{
		std::cout << "                               Explorer                              " << std::endl;
		if(now != nullptr)
		std::cout <<"地址：" << ReadAdd()<< std::endl;
		if (mouse != nullptr)
		{
			std::cout << "当前指向" << std::endl;
			if (mouse->data->Type == true)
				std::cout << mouse->data->File->name_ << std::endl;
			else
				std::cout<< mouse->data->Folder->name_ << std::endl;
		}
		if (add.empty())
		{
			for (Disk_n::Disk_s* it : mydisk->partition_)
			{
				std::cout << it->name << ' ' << it->now_size << "可用" << ' ' << "共" << it->size << std::endl;
			}
		}
		else
		{
			if (now->left_child == nullptr)
			{
				std::cout << "此文件夹为空" << std::endl;
			}
			RightOrder(now->left_child);
		}
	}

	std::string Explorer::GetMouse()
	{
		if (mouse->data != nullptr)
		{
			return mouse->data->File->name_;
		}
		else
		{
			return mouse->data->Folder->name_;
		}
	}

	


	/*
	* @brief  运行函数
	*/
	void Explorer::Run()
	{
		Show();
		GetCommand();
	}
	
	/*
	* @brief 获取输入的名字
	*/
	void Explorer::GetInputName()
	{
		std::cout << "文件名";
		std::cin >> data->name;
	}

	/*
	* @brief 获取文件编写者
	 */
	void Explorer::GetInputOwner()
	{
		std::cout << "拥有者";
		std::cin >> data->owner;
	}

	/*
	*  @brief 获取文件大小
	*/
	void Explorer::GetInputSize()
	{
		std::cout << "大小";
		std::cin >> data->size;
	}

	/*
	*  @brief 获取输入命令
	*/
	void Explorer::GetInputCommand()
	{
		std::cout << "文件类型";
		std::cin >> data->file_type;
	}

	

	

	/*
	* @brief 左遍历
	* @param 需要遍历结点
	*/
	static void LeftOrder(BinaryTree_n::node<Disk_n::Key_s *> *root_)
	{
		if (root_ != nullptr)
		{
			LeftOrder(root_->left_child);
			if(root_->data->Type == true)
			std::cout << root_->data->File->name_<<'.'<<root_->data->File->GetFileType()<< std::endl;
			else
			std::cout << root_->data->Folder->name_ << std::endl;
		}
	}

	/*
	*  @brief  右遍历
	*  @param 需要遍历的结点
	*/
	static void RightOrder(BinaryTree_n::node<Disk_n::Key_s*>* root_)
	{
		if (root_ != nullptr)
		{
			RightOrder(root_->right_child);
			if (root_->data->Type == true)
				std::cout << root_->data->File->name_ << '.' << root_->data->File->file_type << std::endl;
			else
				std::cout << root_->data->Folder->name_ << std::endl;
		}
	}

	/*
	* @brief 结点查找
	* @param root_ 需要查找结点的根
	* @param name 查找的键值
	*/
	static BinaryTree_n::node<Disk_n::Key_s*> *root_search(BinaryTree_n::node<Disk_n::Key_s*>* root_,std::string name)
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1 = nullptr;
		if (root_ != nullptr)
		{
			temp1 = root_; 
			while (1)
			{  
				if(temp1 == nullptr)
				{
					break;
				}
				if (temp1->data->Type == false )
				{
					if (temp1->data->Folder->name_ == name)
					{
						std::cout << temp1->data->Folder->GetAddress() << std::endl;
					}
				}
				if (temp1->data->Type == true)
				{
					if (temp1->data->File->name_ == name)
					{
						std::cout<< temp1->data->File ->GetAddress()<< std::endl;
					}
				}
				temp1 = temp1->right_child;
			}
			return nullptr;
		}
	}
}




