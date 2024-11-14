#include "File_c.hpp"


namespace File_n
{
	File_c::File_c(std::string owner, std::string name, double size) :FileNode_c(FILE, name, size), owner_(owner) {}

	void File_c::ChangeOwner(std::string owner)
	{
		owner_ = owner;
	}

	bool File_c::Open()
	{
		return false;
	}

	bool File_c::Close()
	{
		return false;
	}

}
