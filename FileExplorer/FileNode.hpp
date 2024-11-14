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

namespace File_n
{
  typedef enum
 {
	FOLEDER,
	FILE
  }FFType_e;

  typedef struct
  {
	   
  };

  class FileNode_c
{
  protected:
   std::string name_;  //文件名字
	FFType_e type_;                //文件类型
	double size_;                      //文件大小
	std::string create_time_;                 //创建时间
  public:
	FileNode_c(FFType_e type, std::string name);
	FileNode_c(FFType_e type, std::string name, double size);
	bool Rename(std::string name);
	void SetSize(double size); 
	std::string  GetCreateTime();
	FFType_e GetFileType();
};
   
}



