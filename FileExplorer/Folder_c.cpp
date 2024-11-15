#include "Folder_c.hpp"

namespace File_n
{
	/*
	*@brief 创建一个文件夹
	*/
	Folder_c::Folder_c(std::string name) : FileNode_c(FOLEDER, name) {
		contain = new ContainNum;
		contain->file_num = 0; 
		contain->folder_num = 0;
		size_ = 0;
	}

	


	void Folder_c::GetAttributes()
	{
		std::cout << "路径：" << address << std::endl;
		std::cout << "文件类型：" << type_ << std::endl;
		std::cout << "大小：" << size_ << std::endl;
		std::cout << "包含：" << contain->file_num << "个文件" << contain->folder_num << "个子文件夹" << std::endl;
		std::cout << "创建时间：" << create_time_ << std::endl;
	}
}
