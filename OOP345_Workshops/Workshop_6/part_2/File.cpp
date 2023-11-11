// Workshop 6 - STL Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/11/05

#include <iostream>
#include "File.h"

namespace sdds {
	// Assign the m_name of the Resource parent class and m_contents to received parameters.
	File::File(const std::string& name, const std::string& contents) : m_contents{contents} {
		Resource::m_name = name;
	}

	// Update m_parent_path of Resource object
	void File::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
	}

	// Return Flags::FILE.
	NodeType File::type() const	
	{
		return NodeType::FILE;
	}

	// Return absolute path of the file.
	std::string File::path() const
	{
		return m_parent_path + m_name;
	}

	// Return m_name.
	std::string File::name() const
	{
		return Resource::m_name;
	}

	// Return -1.
	int File::count() const
	{
		return -1;
	}

	// Return size of m_contents.
	size_t File::size() const
	{
		return m_contents.size();
	}
}
