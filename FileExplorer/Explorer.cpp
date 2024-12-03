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
	                                                                          "/search 查找路径",
	                                                                          "/exit 结束程序"};
	Explorer::Explorer()
	{
		mydisk = Disk_n::Disk_c::myDisk;
		mydisk->CreatePartition("C:", 1024, Disk_n::LOCAL, Disk_n::NTFS);
		mydisk->CreatePartition("D:", 2048, Disk_n::LOCAL, Disk_n::NTFS);
	}

	int Explorer::GetCommand()
	{
		std::string name;
		int size;
		std::string owner;
		std::string file_type;
		std::string  command;
		std::string  temp;
		std::string mess;
		size_t i = 0;
		size_t j = 0;
		std::cin >> command;
		if (command.at(0) == '/')
		{
			i = command.find_first_of('/');
			temp = command.substr(i + 1);
			system("cls");
			if (temp == "help") 
			{
				Help();
			}
			else if (temp == "Mouse")
			{
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
				std::cout << "进入哪个盘:";
				std::cin >> temp;
				GoInto(temp);
			}
			else if (temp == "createFile")
			{
				std::cout << "文件名";
				std::cin >> name;
				std::cout << "大小";
				std::cin >> size;
				std::cout << "拥有者";
				std::cin >> owner; 
				std::cout << "文件类型";
				std::cin >> file_type;
				CreateFile(owner,name,size,file_type);
			}
			else if (temp == "deleteFile")
			{
				std::cout << "文件名";
				std::cin >> name;
				DeleteFile(name);
			}
			else if (temp == "createFolder")
			{
				std::cout << "文件名";
				std::cin >> name;
				CreateFolder(name);
			}
			else if (temp == "deleteFolder")
			{
				std::cout << "文件名";
				std::cin >> name;
				DeleteFolder(name);
			}
			else if (temp == "search")
			{
				Search();
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
	void Explorer::Help()
	{
		for (std::string  temp : command_Group)
		{
			std::cout << temp << std::endl;
		}
	}

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

	void Explorer::ReadTree()
	{


	}

	void Explorer::ReadAdd()
	{

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

	void Explorer::GoInto(std::string temp)
	{
		BinaryTree_n::node<Disk_n::Key_s*>*nodetemp = nullptr;
		if (add.empty())
		{
			now_disk =  mydisk->GetPartition(temp);
			now = now_disk->root_->GetTreeRoot();
			now->data = new  Disk_n::Key_s; 
			now->data->Folder = new File_n::Folder_c(now_disk->name);
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

	void Explorer::CreateFile(std::string owner, std::string name, double size,std::string file_type)
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1 = now->left_child;

		Disk_n::Key_s* mykey = new Disk_n::Key_s;
		mykey->Type = true;
		mykey->File = new File_n::File_c(owner, name, size,file_type); 

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

	void Explorer::DeleteFile(std::string name)
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1;
		BinaryTree_n::node<Disk_n::Key_s*>* temp2;
		now->data->Folder->deleteFile();
		if (now->left_child != nullptr)
		{
			if (now->left_child->data->Type == true)
			{
				if (now->left_child->data->File->name_ == name)
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
				if (temp1->data->File->name_ == name)
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

	void Explorer::CreateFolder(std::string name)
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1 = now->left_child;

		Disk_n::Key_s* mykey = new Disk_n::Key_s;
		mykey->Type = false;
		mykey->Folder = new File_n::Folder_c(name);

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

	void Explorer::DeleteFolder(std::string name)
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp1;
		BinaryTree_n::node<Disk_n::Key_s*>* temp2;
		now->data->Folder->deleteFolder();
		if (now->left_child != nullptr)
		{
			if (now->left_child->data->Type == true)
			{
				if (now->left_child->data->File->name_ == name)
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
				if (temp1->data->Folder->name_ == name)
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

	void Explorer::Search()
	{
	}

	void  Explorer::Exit()
	{

	}

	void Explorer::Show()
	{
		std::cout << "                               Explorer                              " << std::endl;
		std::cout <<"地址：" << now->data->Folder->GetAddress() << std::endl;
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

	void Explorer::Run()
	{
		Show();
		GetCommand();


	}

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
						return temp1;
					}
				}
				temp1 = temp1->right_child;
			}
			return nullptr;
		}
	}
}




