#pragma once

#include "disk_c.hpp"
#include <stack>
#include <string>
#include <vector>

namespace Explorer_n {
  
    typedef enum
    {
        FILE,
        FOLDER,
    }Type_e;

    typedef  struct
    {
        unsigned int address;
        Type_e Type;
    }SeachHight;

  class Explorer
  {
    private:
        std::stack<SeachHight> add;
        std::string address;
        File_n::Folder_c *nowpos1;
        File_n::File_c *nowpos2;
        Type_e nowtype;
    public:
        
       
        Explorer();
        int GetCommand();
        void Help();
        void ReadAttributes();
        void ReadTree();
        void ReadAdd();
        void GoBack();
        void GoInto();
        void CreateFile();
        void DeleteFile();
        void CreateFolder();
        void DeleteFolder();
        void Search();
        void Exit();
        void Run();
  };
}




