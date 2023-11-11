// Workshop 6 - STL Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/11/05

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include "Resource.h"
#include "Flags.h"

namespace sdds
{
	class File : public Resource {
		std::string m_contents{};
	public:
		/*
		A custom constructor that receives two strings as parameters:
			- The name of the file
			- A text representation of the contents of a file (optional, with empty string as a default value).
		*/
		File(const std::string& name, const std::string& contents = "");

		// Sets the parent path to the parameter.
		void update_parent_path(const std::string&) override;

		// A query that returns Flags::FILE
		NodeType type() const override;

		// A query that returns the full absolute path of the file (concatenates the absolute path location and the file name).
		std::string path() const override;

		// A query that returns the name of the file.
		std::string name() const override;

		// A query that returns -1.
		int count() const override;

		// A query that returns the size of the file in bytes. 
		// For simplicity, this is the number of characters in m_contents attribute.
		size_t size() const override;
	};

}
#endif //!SDDS_FILE_H
