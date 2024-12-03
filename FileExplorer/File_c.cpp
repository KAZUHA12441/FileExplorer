#include "File_c.hpp"
#include "time_c.hpp"

namespace File_n
{
	/*
	* ����һ���ļ�
	*/
	File_c::File_c(std::string owner, std::string name, double size,std::string file_type) :FileNode_c(FILE, name, size), owner_(owner),file_type(file_type) {
		vistit_time_ = create_time_; 
	}

	/*
	* @brief �޸�ӵ����
	* @param owner �µ�ӵ����
	*/
	void File_c::ChangeOwner(std::string owner)
	{
		owner_ = owner;
	}
	/*
	* @brief �ļ���
	* @return ����ֵ�򿪳ɹ�/ʧ��
	*/
	bool File_c::Open()
	{
		Time_c* now = Time_c::GetInstance();
		vistit_time_ = now->GetNowTime(YMD_HMS);
		/*
		      code
		*/
		return false;
	}


	/*
	* @brief  �ر��ļ�
	* @return ��Ϊ֮
	*/
	bool File_c::Close()
	{
		return false;
	}

	void File_c::GetAttributes()
	{

		std::cout << "·����" << address << std::endl;
		std::cout << "�ļ����ͣ�" << type_ << std::endl;
		std::cout << "��С��" << size_ << std::endl;
		std::cout << "ӵ���ߣ�" << owner_ << std::endl;
		std::cout << "����ʱ�䣺" << create_time_ << std::endl;
		std::cout << "����ʱ�䣺" << vistit_time_ << std::endl;
	}

}
