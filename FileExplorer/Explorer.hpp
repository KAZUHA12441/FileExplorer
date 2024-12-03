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

   

  class Explorer
  {
    private:
        std::stack<BinaryTree_n::node<Disk_n::Key_s*>*> add;
        std::string address;
        Disk_n::Disk_c* mydisk = nullptr;
        Disk_n::Disk_s  *now_disk = nullptr;
        BinaryTree_n::node<Disk_n::Key_s*>* now = nullptr;
        BinaryTree_n::node<Disk_n::Key_s*>* mouse = nullptr;
    public:
        
       
        Explorer();
        int GetCommand();
        void Help();
        void ReadAttributes();
        void ReadTree();
        void ReadAdd();
        void GoBack();
        void GoInto(std::string temp);
        void CreateFile(std::string owner, std::string name, double size,  std::string file_type);
        void DeleteFile(std::string name);
        void CreateFolder(std::string name);
        void DeleteFolder(std::string name);
        void Rename();
        void Mouse();
        void Search();
        void Exit();
        void Run();
        void Show();
        
  };
  static void LeftOrder(BinaryTree_n::node<Disk_n::Key_s*>* root_);
  static void RightOrder(BinaryTree_n::node<Disk_n::Key_s*>* root_);
  static BinaryTree_n::node<Disk_n::Key_s*>*root_search(BinaryTree_n::node<Disk_n::Key_s*>* root_, std::string name);
}




