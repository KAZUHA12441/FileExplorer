/*****************************************************************//**
 * \file   FileNode.cpp
 * \brief  
 * 
 * \author �����
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
	* @brief �ļ�������
	* @param type �ļ�����
	* @param name �ļ���
	* @param size ��С
	*/
	FileNode_c::FileNode_c(FFType_e type, std::string name, double size) :type_(type), size_(size), name_(name)
	{
		Time_c* now = Time_c::GetInstance();
		create_time_ = now->GetNowTime(YMD_HMS);
	}

	/*
	* @brief �ļ�������
	* @param ����
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
	 * \param size  ��С
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
