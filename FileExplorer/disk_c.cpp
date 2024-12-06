#include "disk_c.hpp"

namespace  Disk_n
{

	Disk_c* Disk_c::myDisk = new  Disk_c("DEMO", 102400);
	/*
	* @brief 磁盘构造
	* @param name 
	* @param physical_size_
	*/
	Disk_c::Disk_c(std::string name, float phyical_size_)
	{
		this->name = name;
		this->physical_size_ = phyical_size_;
		std::cout << "磁盘正在运行！" << std::endl;
	}

	/*
	* @brief 创建磁盘分区
	* @param name 磁盘名
	* @param size 需要分区的大小
	* @param Dtype 磁盘类型
	* @param Etype  文件系统
	*/
	bool Disk_c::CreatePartition(std::string name, float size, DiskType_e Dtype, ExplorType_e Etype)
	{
		Disk_s* temp = new Disk_s;
		temp->name = name;
		temp->Dtype = LOCAL;
		temp->Etype = NTFS;
		temp->now_size = size;
		if (physical_size_ - now_size_ >= size)
		{
			temp->size = size;
			now_size_ += size;
		}
		else
		{
			std::cout << "error:" << "磁盘空间不足，无法分区" << std::endl;
			while (1); //中断
			return false;
		}
		temp->root_ = new BinaryTree_n::BinaryTree_c<Key_s*>;
		partition_.push_back(temp);
		return true;
	}

	/**
	 * .
	 * 
	 * \param name 磁盘名
	 * \return 磁盘结构体指针
	 */
	Disk_s* Disk_c::GetPartition(std::string  name)
	{
		for (Disk_s* it : partition_)
		{
			if (it->name==name)
			{
				std::cout << it->name << std::endl;
				return it;
			}
		}
		std::cout << "error:" << "无对应磁盘" << std::endl;
		return nullptr;
	}
	/*
	* @brief 删除分区
	* @param name 删除磁盘名
	* @return 布尔值
	*/
	bool  Disk_c::DeletePartiton(std::string name)
	{
		int i = -1;
		for (Disk_s* it : partition_)
		{
			i++;

			if (it->name.compare(name)) //比较字符串
			{
				delete it;
				partition_.erase(partition_.begin()+ i);   //擦除
				return true;
			}
		}
		std::cout << "warring:" << "未找到对应磁盘" << std::endl;
			return false;
	}

	float Disk_c::GetFreeSpace(std::string name)
	{
		for (Disk_s* it : partition_)
		{
			if (it->name.compare(name))
			{
				return  it->now_size;
			}
		}
		std::cout << "warring:" << "未找到对应磁盘" << std::endl;
		return 0;
	}

	Disk_c* Disk_c::GetInstance()
	{
		return myDisk;
	}

	/*
	* @brief 增加当前容量
	*/
	void  Disk_c::UpNowSize(Disk_s* now_disk, int size)
	{
		now_disk->now_size += size;
	}

	/*
	* @brief  减少当前容容量
	*/
	void Disk_c::DownNowSize(Disk_s* now_disk, int size)
	{
		if (now_disk->now_size > size)
			now_disk->now_size -= size;
		else
			std::cout << "空间不足" << std::endl; 
	}
}
 