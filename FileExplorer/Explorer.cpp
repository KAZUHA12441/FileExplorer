#include "Explorer.hpp"
#include <iostream>
#include <fstream>

namespace Explorer_n
{
	std::string  command_Gruop[] = {"/Help �鿴����", "/"};
	Explorer::Explorer()
	{
		
	}

	int Explorer::GetCommand()
	{
		std::string  command;
		std::string  temp;
		size_t i = 0;
		std::cin >> command;
		if (command.at(0) == '/')
		{
			i = command.find_first_of('/'); 
			temp = command.substr(i+1);
			if (temp == "help")
			{
				Help();
			}
			else if (temp == "readAttributes")
			{
				ReadAttributes();
			}
			else if (temp == ":readTree")
			{
				ReadTree();
			}
			else if (temp == "readAdd")
			{
				ReadAdd();
			}
			else if (temp == "goBack")
			{
				GoBack();
			}
			else if (temp == "goInto")
			{
				GoInto();
			}
			else if (temp == "createFile")
			{
				CreateFile();
			}
			else if (temp == "deleteFile")
			{
				DeleteFile();
			}
			else if (temp == "createFolder")
			{
				CreateFolder();
			}
			else if (temp == "deleteFolder")
			{
				DeleteFolder();
			}
			else if (temp == "search")
			{
				Search();
			}
			else if (temp == "exit")
			{
				Exit();
			}
			else
			{
				std::cout << "���������" << "����help��ѯ��������" << std::endl;
			}
		}
		else
		{
			std::cout << "��ʽ����" << std::endl;
		}

		return 0;
	}
	void Explorer::Help()
	{

	}
	void Explorer::ReadAttributes()
	{
	}

	void Explorer::ReadTree()
	{
	}

	void Explorer::ReadAdd()
	{
	}

	void Explorer::GoBack()
	{
	}

	void Explorer::GoInto()
	{
	}

	void Explorer::CreateFile()
	{
	}

	void Explorer::DeleteFile()
	{
	}

	void Explorer::CreateFolder()
	{
	}

	void Explorer::DeleteFolder()
	{
	}

	void Explorer::Search()
	{
	}

	void  Explorer::Exit()
	{

	}


	void Explorer::Run()
	{
		
		GetCommand();


	}

}




