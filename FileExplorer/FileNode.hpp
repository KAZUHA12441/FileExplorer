/*****************************************************************//**
 * \file   FileNode.hpp
 * \brief   �ļ����� 
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
   std::string name_;  //�ļ�����
	FFType_e type_;                //�ļ�����
	double size_;                      //�ļ���С
	std::string create_time_;                 //����ʱ��
  public:
	FileNode_c(FFType_e type, std::string name);
	FileNode_c(FFType_e type, std::string name, double size);
	bool Rename(std::string name);
	void SetSize(double size); 
	std::string  GetCreateTime();
	FFType_e GetFileType();
};
   
}



