#pragma once
#include "File_c.hpp"
#include "Folder_c.hpp"
#include "BinaryTree.hpp"
#include <vector>
#include "BinaryTree.cpp"

namespace Disk_n
{

    typedef enum
    {
        LOCAL,
        MOVABLE,
    }DiskType_e;

    typedef enum
    {
        NTFS,
        exFAT,
        FAT32
    }ExplorType_e;

    typedef struct
    {
        File_n::File_c* File; 
        File_n::Folder_c* Folder;
        bool Type;
    }Key_s;

    typedef  struct
    {
        std::string  name;
        float  size;
        float now_size;
        DiskType_e Dtype;
        ExplorType_e Etype;
        BinaryTree_n::BinaryTree_c<Key_s *> *root_;
    }Disk_s;

  class Disk_c
 {
 protected:
     std::string name;
     float physical_size_ = 102400;                   //byte
     float now_size_ = 0;
     std::vector<Disk_s *> partition_;
 public:
     static  Disk_c* myDisk;
     Disk_c(std::string name,float physicl_size);
     bool  CreatePartition(std::string name,float size, DiskType_e Dtype, ExplorType_e Etype);
     Disk_s* GetPartition(std::string  name);
     bool DeletePartiton(std::string name);
     float GetFreeSpace(std::string name);
     static Disk_c* GetInstance();
 };
}


