/*****************************************************************//**
 * \file   FileNode.hpp
 * \brief   文件父类 
 * 
 * \author Peter
 * \date   November 2024
 *********************************************************************/


#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>


namespace File_n
{
  typedef enum
 {
	FOLEDER,
	FILE
  }FFType_e;

  class FileNode_c
{
  protected:
	std::string  address;
                                            //文件名字
	FFType_e type_ = FILE;                                            //文件类型
	double size_ = 0;                                                           //文件大小
	std::string create_time_= "1970/01/01";                //创建时间
  public:
	std::string name_;
	FileNode_c(FFType_e type, std::string name);
	FileNode_c(FFType_e type, std::string name, double size);
	bool Rename(std::string name);
	void SetSize(double size); 
	std::string  GetCreateTime();
	FFType_e GetFileType();
	void  SetAddress(std::string address);

	virtual void GetAttributes() = 0;
};
   
}



