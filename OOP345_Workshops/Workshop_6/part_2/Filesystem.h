// Workshop 6 - STL Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/11/05

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <iostream>
#include <vector>
#include "File.h"
#include "Flags.h"
#include "Directory.h"

namespace sdds
{
	class Filesystem {
		Directory* m_root{};
		Directory* m_current{};

	public:
		// A custom constructor that receives the name of a file as its first argument, 
		// and an optional string containing the name of the root directory (defaults to an empty string)
		Filesystem(const std::string& filename, const std::string& rootDir = "");

		// Adds a resource to the current directory.
		Filesystem& operator+=(Resource*);

		// Changes the current directory to the directory (located in the current directory) whose name matches argument.
		Directory* change_directory(const std::string& dir = "");

		// A query that returns the current directory.
		Directory* get_current_directory() const;

		// Rules of five
		~Filesystem();
		Filesystem(const Filesystem&) = delete;				// Prevent from copy constructor.
		Filesystem& operator=(const Filesystem&) = delete;	// Prevent from copy assignment operator.
		Filesystem(Filesystem&&);							// Move constructor.
		Filesystem& operator=(Filesystem&&);				// Move assignment operator.
	};
}
#endif //!SDDS_FILESYSTEM_H