#pragma once

#include "disk_c.hpp"
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 

namespace Explorer_n {
  
    typedef enum
    {
        FILE,
        FOLDER,
    }Type_e;

    typedef struct
    {
        std::string name;
        int size;
        std::string owner;
        std::string file_type;
        std::string  command;
       
       
    }InputData_s;

  class Explorer
  {
    private:
        void GetInputName();
        void GetInputOwner();
        void GetInputSize();
        void GetInputFile();
        void Init();
        void Inputfile(std::string temp);
        BinaryTree_n::node<Disk_n::Key_s*> *FindFolder();
        void Destroy(BinaryTree_n::node<Disk_n::Key_s*>* root);
        std::fstream* file = nullptr;

        std::stack<BinaryTree_n::node<Disk_n::Key_s*>*> add;
        std::string address;
        Disk_n::Disk_c* mydisk = nullptr;
        Disk_n::Disk_s  *now_disk = nullptr;
        BinaryTree_n::node<Disk_n::Key_s*>* now = nullptr;
        BinaryTree_n::node<Disk_n::Key_s*>* mouse = nullptr;
        InputData_s * data;
        bool InitCp  = false; 
        bool frist = false;
    public:
        
       
        Explorer();
        
        int GetCommand();
        void Help();
        void ReadAttributes();
        std::string ReadAdd();
        void GoBack();
        void GoInto(std::string temp);
        void CreateFile();
        void DeleteFile();
        void CreateFolder();
        void DeleteFolder();
        void Rename(std::string name);
        void Mouse();
        void Search(std::string name);
        void Exit();
        void Run();
        void Show();
        
        std::string GetMouse();
  };
  static void LeftOrder(BinaryTree_n::node<Disk_n::Key_s*>* root_);
  static void RightOrder(BinaryTree_n::node<Disk_n::Key_s*>* root_);
  static BinaryTree_n::node<Disk_n::Key_s*>*root_search(BinaryTree_n::node<Disk_n::Key_s*>* root_, std::string name);
}




