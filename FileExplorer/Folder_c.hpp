#pragma once

#include  "FileNode.hpp"
namespace File_n
{
	typedef struct
	{
		int file_num;
		int folder_num;
	}ContainNum;

	class Folder_c :public FileNode_c
	{
	  public: 
		  ContainNum* contain;
		  Folder_c(std::string name);
		  void GetAttributes();
	};
}

