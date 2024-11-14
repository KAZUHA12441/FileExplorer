#include "Folder_c.hpp"

namespace File_n
{
	Folder_c::Folder_c(std::string name) : FileNode_c(FOLEDER, name) {
		contain = new ContainNum;
		contain->file_num = 0; 
		contain->folder_num = 0;
	}
	
}
