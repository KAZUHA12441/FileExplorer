/*****************************************************************//**
 * \file   FileNode.cpp
 * \brief  
 * 
 * \author 王道楸
 * \date   November 2024
 *********************************************************************/
#include "FileNode.hpp"
#include "time_c.hpp"

namespace File_n
{
	FileNode_c::FileNode_c(FFType_e type, std::string name) :type_(type), name_(name)
	{
		Time_c* now = Time_c::GetInstance();
		create_time_ = now->GetNowTime(YMD_HMS);
	}

	/*
	* @brief 文件父构造
	* @param type 文件类型
	* @param name 文件名
	* @param size 大小
	*/
	FileNode_c::FileNode_c(FFType_e type, std::string name, double size) :type_(type), size_(size), name_(name)
	{
		Time_c* now = Time_c::GetInstance();
		create_time_ = now->GetNowTime(YMD_HMS);
	}

	/*
	* @brief 文件重命名
	* @param 名字
	*  
	*/
    bool FileNode_c::Rename(std::string name)
	{ 
		try
		{
           name_ = name;
		    return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	/**
	 * .
	 * 
	 * \param size  大小
	 */
	void FileNode_c::SetSize(double size)
	{
		size_ = size;
	}

	std::string  FileNode_c::GetCreateTime()
	{
		return create_time_;
	}

	FFType_e  FileNode_c::GetFileType()
	{
		return  type_;
	}

	void FileNode_c::SetAddress(std::string address)
	{
		this->address = address;
	}
}
