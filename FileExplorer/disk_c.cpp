#include "disk_c.hpp"

namespace  Disk_n
{

	Disk_c* Disk_c::myDisk = new  Disk_c("DEMO", 102400);
	/*
	* @brief ���̹���
	* @param name 
	* @param physical_size_
	*/
	Disk_c::Disk_c(std::string name, float phyical_size_)
	{
		this->name = name;
		this->physical_size_ = phyical_size_;
		std::cout << "�����������У�" << std::endl;
	}

	/*
	* @brief �������̷���
	* @param name ������
	* @param size ��Ҫ�����Ĵ�С
	* @param Dtype ��������
	* @param Etype  �ļ�ϵͳ
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
			std::cout << "error:" << "���̿ռ䲻�㣬�޷�����" << std::endl;
			while (1); //�ж�
			return false;
		}
		temp->root_ = new BinaryTree_n::BinaryTree_c<Key_s*>;
		partition_.push_back(temp);
		return true;
	}

	/**
	 * .
	 * 
	 * \param name ������
	 * \return ���̽ṹ��ָ��
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
		std::cout << "error:" << "�޶�Ӧ����" << std::endl;
		return nullptr;
	}
	/*
	* @brief ɾ������
	* @param name ɾ��������
	* @return ����ֵ
	*/
	bool  Disk_c::DeletePartiton(std::string name)
	{
		int i = -1;
		for (Disk_s* it : partition_)
		{
			i++;

			if (it->name.compare(name)) //�Ƚ��ַ���
			{
				delete it;
				partition_.erase(partition_.begin()+ i);   //����
				return true;
			}
		}
		std::cout << "warring:" << "δ�ҵ���Ӧ����" << std::endl;
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
		std::cout << "warring:" << "δ�ҵ���Ӧ����" << std::endl;
		return 0;
	}

	Disk_c* Disk_c::GetInstance()
	{
		return myDisk;
	}

	/*
	* @brief ���ӵ�ǰ����
	*/
	void  Disk_c::UpNowSize(Disk_s* now_disk, int size)
	{
		now_disk->now_size += size;
	}

	/*
	* @brief  ���ٵ�ǰ������
	*/
	void Disk_c::DownNowSize(Disk_s* now_disk, int size)
	{
		if (now_disk->now_size > size)
			now_disk->now_size -= size;
		else
			std::cout << "�ռ䲻��" << std::endl; 
	}
}
 