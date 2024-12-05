#include "Explorer.hpp"
#include <iostream>
#include <fstream>

namespace Explorer_n
{
	std::vector< std::string>  command_Group = {"/help �鿴����", 
		                                                                      "/readAttributes �鿴����",
		                                                                      "/readTree �鿴�ļ���",
		                                                                      "/readAdd �鿴��ǰ��ַ",
	                                                                          "/goBack �ص���һ��",
	                                                                          "/goInto ������һ��",
	                                                                          "/createFile �ڵ���Ŀ¼�´���һ���ļ�",
	                                                                          "/deleteFile ɾ����ǰĿ¼�µ�һ���ļ�",
	                                                                          "/createFolder �ڵ�ǰĿ¼�´���һ���ļ���",
	                                                                          "/deleteFolder ɾ����ǰĿ¼�µ�һ���ļ���",
		                                                                      "/Rename ���ļ������ļ��н���������"
	                                                                          "/search ����·��",
	                                                                          "/exit ��������"};
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
				std::cout << "���������" << "����help��ѯ��������" << std::endl;
			}
		}
		else
		{
			std::cout << "��ʽ����" << std::endl;
		}

		return 0;
	}

	/*
	*  @brief  �����б�
	*/
	void Explorer::Help()
	{
		for (std::string  temp : command_Group)
		{
			std::cout << temp << std::endl;
		}
	}


	/*
	* @brief �鿴�ļ�����
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
	* @�鿴�ļ���
	*/
	void Explorer::ReadTree()
	{


	}

	/*
	* @brief �鿴�ļ���ַ
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
	* @brief  ����һ���ļ���
	* @param  temp �������ļ���
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
					std::cout << "�޴��ļ���" << std::endl;
				}
		}
	}

	/*
	* @brief  �����ļ�
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
	* @brief ɾ��ĳ���ļ�
	* @name ��Ҫɾ�����ļ�
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
					std::cout << "�Ҳ������ļ�" << std::endl;
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
			std::cout << "�Ҳ����ļ�" << std::endl;
		}
	}

	/*
	* @brief  ����һ���ļ���
	* @param �����ļ�����
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
	* @brief ɾ��һ���ļ���
	* @param ɾ���ļ��е�����
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
					std::cout << "�Ҳ������ļ�" << std::endl;
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
			std::cout << "�Ҳ����ļ�" << std::endl;
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
	* @brief ���/�α�?
	*/
	void  Explorer::Mouse()
	{
		mouse = root_search(now, data->name);
	}
	





	/*
	* @brief ��ʾ����
	*/
	void Explorer::Show()
	{
		std::cout << "                               Explorer                              " << std::endl;
		if(now != nullptr)
		std::cout <<"��ַ��" << ReadAdd()<< std::endl;
		if (mouse != nullptr)
		{
			std::cout << "��ǰָ��" << std::endl;
			if (mouse->data->Type == true)
				std::cout << mouse->data->File->name_ << std::endl;
			else
				std::cout<< mouse->data->Folder->name_ << std::endl;
		}
		if (add.empty())
		{
			for (Disk_n::Disk_s* it : mydisk->partition_)
			{
				std::cout << it->name << ' ' << it->now_size << "����" << ' ' << "��" << it->size << std::endl;
			}
		}
		else
		{
			if (now->left_child == nullptr)
			{
				std::cout << "���ļ���Ϊ��" << std::endl;
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
	* @brief  ���к���
	*/
	void Explorer::Run()
	{
		Show();
		GetCommand();
	}
	
	/*
	* @brief ��ȡ���������
	*/
	void Explorer::GetInputName()
	{
		std::cout << "�ļ���";
		std::cin >> data->name;
	}

	/*
	* @brief ��ȡ�ļ���д��
	 */
	void Explorer::GetInputOwner()
	{
		std::cout << "ӵ����";
		std::cin >> data->owner;
	}

	/*
	*  @brief ��ȡ�ļ���С
	*/
	void Explorer::GetInputSize()
	{
		std::cout << "��С";
		std::cin >> data->size;
	}

	/*
	*  @brief ��ȡ��������
	*/
	void Explorer::GetInputCommand()
	{
		std::cout << "�ļ�����";
		std::cin >> data->file_type;
	}

	

	

	/*
	* @brief �����
	* @param ��Ҫ�������
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
	*  @brief  �ұ���
	*  @param ��Ҫ�����Ľ��
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
	* @brief ������
	* @param root_ ��Ҫ���ҽ��ĸ�
	* @param name ���ҵļ�ֵ
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




