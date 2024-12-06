#include "Explorer.hpp"

namespace Explorer_n
{
	std::vector< std::string>  command_Group = { "/help 查看命令",
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
																			  "/exit 结束程序" };
	Explorer::Explorer()
	{

		file = new std::fstream();
		mydisk = Disk_n::Disk_c::myDisk;
		mydisk->CreatePartition("C:", 1024, Disk_n::LOCAL, Disk_n::NTFS);
		mydisk->CreatePartition("D:", 2048, Disk_n::LOCAL, Disk_n::NTFS);
		data = new InputData_s;
	}

	/*
	* @brief 获取命令
	*/
	int Explorer::GetCommand()
	{
		std::string  temp;
		std::string mess;
		size_t i = 0;
		size_t j = 0;
		if(InitCp == true)
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
				if (InitCp == true)
				{
					Inputfile(data->command);
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
					GetInputName();
				}
				Mouse();
			}
			else if (temp == "readAttributes")
			{
				
				ReadAttributes();
			}
			else if (temp == "readAdd")
			{
				ReadAdd();
			}
			else if (temp == "goBack")
			{
				if (InitCp == true)
				{
					Inputfile(data->command);
				}
				GoBack();
			}
			else if (temp == "goInto")
			{	
				if (InitCp == true)
				{
					Inputfile(data->command);	
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
					GetInputName();
				}
			
				GoInto(data->name);
			}
			else if (temp == "createFile")
			{
				if (InitCp == true)
				{
				  Inputfile(data->command); 
				  GetInputName();
				  GetInputSize();
				  GetInputOwner();
				  GetInputFile();
                  Inputfile(data->name);
				  file->open("file.dat", std::ios::app);
				  if (!*file) {
					  std::cerr << "Unable to open file!" << std::endl;
					  while (1);
				  }
				 *file << std::to_string(data->size) << std::endl;
				 file->close();
				  Inputfile(data->owner);
				  Inputfile(data->file_type);
				}
				else
				{
				   GetInputName();
				   GetInputSize();
				   GetInputOwner();
				   GetInputFile();
				}
	              
				CreateFile();
			}
			else if (temp == "deleteFile")
			{
				
				if (InitCp == true)
				{
					Inputfile(data->command);
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
					 GetInputName();
				}

				DeleteFile();
			}
			else if (temp == "createFolder")
			{
				if (InitCp == true)
				{
					Inputfile(data->command);
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
                     GetInputName();
				}
				CreateFolder();
			}
			else if (temp == "deleteFolder")
			{
				
				if (InitCp == true)
				{
					Inputfile(data->command);
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
					 GetInputName();
				}
				DeleteFolder();
			}
			else if (temp == "search")
			{    
				GetInputName();
				Search(data->name);
			}
			else if (temp == "Rename")
			{
				
				if (InitCp == true)
				{

					Inputfile(data->command);
					GetInputName();
					Inputfile(data->name);
				}
				else
				{
                      GetInputName();
				}
				Rename(data->name);
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
		for (std::string temp : command_Group)
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
			if (mouse != nullptr)
			{
              if (mouse->data->Type == true)
			 {
				 mouse->data->File->GetAttributes();
			 }
			 else if (mouse->data->Type == false)
			 {
				 mouse->data->Folder->GetAttributes();
			 }
			}
			
		}
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
		BinaryTree_n::node<Disk_n::Key_s*>* nodetemp = nullptr;
		if (add.empty())
		{
			now_disk = mydisk->GetPartition(temp);
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
			nodetemp = FindFolder();
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
		mykey->File = new File_n::File_c(data->owner, data->name+'.'+ data->file_type, data->size, data->file_type);

		BinaryTree_n::node<Disk_n::Key_s*>* temp2 = new BinaryTree_n::node<Disk_n::Key_s*>;
		temp2->data = mykey;
		temp2->left_child = nullptr;
		temp2->right_child = nullptr;
		now->data->Folder->createFile();

		mydisk->DownNowSize(now_disk, data->size);

		if (!add.empty())
		{
			if (temp1 == nullptr)
			{
				temp2->data->File->SetAddress(now->data->Folder->name_ + "\\" + mykey->File->name_ + '.' + mykey->File->file_type);
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
				if (temp1->data->Type == true)
				{
					if (temp1->data->File->name_ == data->name)
					{
						temp2->right_child = temp1->right_child;
						//增加磁盘容量
						mydisk->UpNowSize(now_disk, temp1->data->File->size_);
						delete temp1;
						break;
					}
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
			temp2->data->Folder->SetAddress(now->data->Folder->name_ + "\\" + mykey->Folder->name_);
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
			if (now->left_child->data->Type == false)
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
				if (temp1->data->Type == false)
				{
                   if (temp1->data->Folder->name_ == data->name)
				  {
					temp2->right_child = temp1->right_child;
					Destroy(temp1->left_child);
					delete temp1;
					break;
				 }
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
		root_search(now->left_child, name);
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
		BinaryTree_n::node<Disk_n::Key_s*>* temp1;
		if (now->left_child != nullptr)
		{
			if (now->left_child->data->Type == true)
			{
				if (now->left_child->data->File->name_ == data->name)
				{
					mouse = now->left_child;
					return;
				}
			}
			else
			{
				if (now->left_child->data->Folder->name_ == data->name)
				{
					mouse = now->left_child;
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
				if (temp1->data->Type == false)
				{
                   if (temp1->data->Folder->name_ == data->name)
				   {
					  mouse = temp1;
					  break;
				   }
				}
				else
				{
                    if (temp1->data->File->name_ == data->name)
				   {
					mouse = temp1;
					break;
				   }
				}
				
					temp1 = temp1->right_child;
			}
		}
		else
		{
			std::cout << "找不到文件" << std::endl;
		}
	}

	/*
	* @brief 显示函数
	*/
	void Explorer::Show()
	{
		std::cout << "                               Explorer                              " << std::endl;
		if (now != nullptr)
			std::cout << "地址：" << ReadAdd() << std::endl;
		if (mouse != nullptr)
		{
			std::cout << "当前指向";
			if (mouse->data->Type == true)
				std::cout << mouse->data->File->name_ << std::endl;
			else
				std::cout << mouse->data->Folder->name_ << std::endl;
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

	/*
	* 获取指向的文件结点
	*/
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
		
		if (!InitCp)
		{
			Init();
		}
		Show();
		GetCommand();
	}

	/*
	* @brief 文件初始化
	 */
	void Explorer::Init()
	{
		if (!frist)
		{
          file->open("file.dat", std::ios::in);
		  frist = true;
		}
		if (!(*file)) {
			std::cerr << "Unable to open file!" << std::endl;
			while (1);
		}
		std::string line;
		if (std::getline(*file, line))
		{
			 data->command = line;
		}
		else
		{
			file->close();
			while (1)
			{
				if (add.empty())
				{
					break;
				}
				GoBack();
				mouse = nullptr;
			}
			InitCp = true;
		}
	}

	
	/*
	* @输入到文件
	*/
	void Explorer::Inputfile(std::string temp)
	{
		file->open("file.dat", std::ios::app);
		if (!*file) {
			std::cerr << "Unable to open file!" << std::endl;
			while (1);
		}
		*file << temp << std::endl;
		file->close();
	}



	/*
	* @brief 获取输入的名字
	*/
	void Explorer::GetInputName()
	{
		std::string line;
		if (InitCp == true)
		{
          std::cout << "文件名";
		  std::cin >> data->name;
		}
		else
		{
			if (std::getline(*file, line))
			{
				data->name = line;
			}
		}
		
	}

	/*
	* @brief 获取文件编写者
	 */
	void Explorer::GetInputOwner()
	{
		std::string line;
		if (InitCp == true)
		{
          std::cout << "拥有者";
		  std::cin >> data->owner;
		}
		else
		{
			if (std::getline(*file, line))
			{
				data->owner = line;
			}
		}
		
	}

	/*
	*  @brief 获取文件大小
	*/
	void Explorer::GetInputSize()
	{
		std::string line;
		if (InitCp == true)
		{
				std::cout << "大小";
		       std::cin >> data->size;
		}
		else
		{
			if (std::getline(*file, line))
			{
				data->size = std::stoi(line);
			}
		}
		
	}

	/*
	*  @brief 获取输入命令
	*/
	void Explorer::GetInputFile()
	{
		std::string line;
		if (InitCp == true)
		{
		std::cout << "文件类型";
		std::cin >> data->file_type;
		}
		else
		{
			if (std::getline(*file, line))
			{
				data->file_type = line;
			}
		}
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
				std::cout << root_->data->File->name_ << std::endl;
			else
				std::cout << root_->data->Folder->name_ << std::endl;
		}
	}

	/*
	* @brief 结点查找
	* @param root_ 需要查找结点的根
	* @param name 查找的键值
	*/
	static BinaryTree_n::node<Disk_n::Key_s*> *root_search(BinaryTree_n::node<Disk_n::Key_s*>*root_, std::string name)
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
		else
		{
			return nullptr;
		}
	}

	/*
	* @brief 找文件夹
	*/
	BinaryTree_n::node<Disk_n::Key_s*>* Explorer::FindFolder()
	{
		BinaryTree_n::node<Disk_n::Key_s*>* temp = nullptr;
		if (now->left_child != nullptr)
		{
			temp = now->left_child;
			while (1)
			{
				if (temp == nullptr)
				{
					break;
				}
				if (temp->data->Type == false)
				{
					if (temp->data->Folder->name_ == data->name)
					{
						return temp;
					}
				}
				temp = temp->right_child;
			}
			return nullptr;
		}
		else
		{
			return nullptr;
		}
	}
	void Explorer::Destroy(BinaryTree_n::node<Disk_n::Key_s*> *root)
	{
		if (root != nullptr && root->left_child != nullptr)
		{
			Destroy(root->left_child);
		}
		else if (root != nullptr && root->right_child != nullptr)
		{
			Destroy(root->right_child);
		}
		if (root->data->Type == true)
		{
			mydisk->UpNowSize(now_disk, root->data->File->size_);
		}
		delete root;
	}
}



 