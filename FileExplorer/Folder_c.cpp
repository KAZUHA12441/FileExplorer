#include "Folder_c.hpp"

namespace File_n
{
	/*
	*@brief ����һ���ļ���
	*/
	Folder_c::Folder_c(std::string name) : FileNode_c(FOLEDER, name) {
		contain = new ContainNum;
		contain->file_num = 0; 
		contain->folder_num = 0;
		size_ = 0;
	}

	void Folder_c::GetAttributes()
	{
		std::cout << "·����" << address << std::endl;
		std::cout << "�ļ����ͣ�" << type_ << std::endl;
		std::cout << "��С��" << size_ << std::endl;
		std::cout << "������" << contain->file_num << "���ļ�" << contain->folder_num << "�����ļ���" << std::endl;
		std::cout << "����ʱ�䣺" << create_time_ << std::endl;
	}

	void Folder_c::createFile()
	{
		contain->file_num++; 
	}
	void Folder_c::createFolder()
	{
		contain->folder_num++;
	}

	void Folder_c::deleteFile()
	{
		if (contain->file_num> 0)
		{
			contain->file_num--;
		 }
	}
	void Folder_c::deleteFolder()
	{
		if (contain->folder_num > 0)
		{
			contain->folder_num--;
		}
	}
	std::string Folder_c::GetAddress()
	{
		return address;
	}
}
