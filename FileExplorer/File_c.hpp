#pragma once
#include "FileNode.hpp"



namespace File_n
{
class File_c :public FileNode_c
{
   public:
	   std::string owner_;
	   std::string  vistit_time_;
	   File_c(std::string owner, std::string name, double size);
	   void ChangeOwner(std::string owner);
	   bool Open();
	   bool Close();
	   void GetAttributes();
};
}


