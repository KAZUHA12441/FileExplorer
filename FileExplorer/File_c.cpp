#include "File_c.hpp"
#include "time_c.hpp"

namespace File_n
{
	/*
	* 创建一个文件
	*/
	File_c::File_c(std::string owner, std::string name, double size,std::string file_type) :FileNode_c(FILE, name, size), owner_(owner),file_type(file_type) {
		vistit_time_ = create_time_; 
	}

	/*
	* @brief 修改拥有者
	* @param owner 新的拥有者
	*/
	void File_c::ChangeOwner(std::string owner)
	{
		owner_ = owner;
	}
	/*
	* @brief 文件打开
	* @return 布尔值打开成功/失败
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
	* @brief  关闭文件
	* @return 不为之
	*/
	bool File_c::Close()
	{
		return false;
	}

	void File_c::GetAttributes()
	{

		std::cout << "路径：" << address << std::endl;
		std::cout << "文件类型：" << type_ << std::endl;
		std::cout << "大小：" << size_ << std::endl;
		std::cout << "拥有者：" << owner_ << std::endl;
		std::cout << "创建时间：" << create_time_ << std::endl;
		std::cout << "访问时间：" << vistit_time_ << std::endl;
	}

}
