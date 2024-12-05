#pragma once
#include "FileNode.hpp"



namespace File_n
{
class File_c :public FileNode_c
{
   public:
	   std::string owner_;
	   std::string  vistit_time_;
	   std::string  file_type;
	   File_c(std::string owner, std::string name, double size, std::string  file_type);
	   void ChangeOwner(std::string owner);
	   bool Open();
	   bool Close();
	   void GetAttributes();
	   std::string GetAddress();
};
}


