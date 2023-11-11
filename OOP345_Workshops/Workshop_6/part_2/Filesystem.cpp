// Workshop 6 - STL Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/11/05

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Filesystem.h"

namespace sdds {
	Filesystem::Filesystem(const std::string& filename, const std::string& rootDir)
	{
		// Dynamic allocate for m_root and set m_current as m_root
		m_root = new Directory(rootDir);
		m_current = m_root;

		// Open file
		std::ifstream file(filename);

		// If file annot open
		if (!file.is_open()) {
			// Release m_root in case of exception
			delete m_root;
			throw std::invalid_argument("**EXPECTED EXCEPTION: Filesystem not created with an invalid filename.");
		}

		// Load the content in a file
		std::string line{};
		while (std::getline(file, line)) {

			// Remove leading and trailing spaces from the line
			line.erase(0, line.find_first_not_of(" \t"));
			line.erase(line.find_last_not_of(" \t") + 1);

			// Split the line into path and contents (if applicable)
			size_t splitPos = line.find(" | ");
			std::string path = line.substr(0, splitPos);
			path.erase(path.find_last_not_of(" \t") + 1);
			std::string contents;

			// If the resource is a file
			if (splitPos != std::string::npos) {
				contents = line.substr(splitPos + 3);
				contents.erase(0, contents.find_first_not_of(" \t"));
			}

			// Create directories and files as needed
			std::vector<std::string> pathComp{};
			size_t start = 0;
			size_t end = path.find('/');
			while (end != std::string::npos) {
				pathComp.push_back(path.substr(start, end - start));
				start = end + 1;
				end = path.find('/', start);
			}
			pathComp.push_back(path.substr(start));

			Directory* currentDir = m_root;
			for (const std::string& component : pathComp) {
				Directory* foundDir = dynamic_cast<Directory*>(currentDir->find(component));

				// If the path is already existed. then update currentDir to the foundDir.
				if (foundDir) {
					currentDir = foundDir;
				}
				// If not create the new new directory and push to the currentDir.
				else {
					// Create the directory if it doesn't exist
					Directory* newDir = new Directory(component);
					newDir->update_parent_path(newDir->name());
					currentDir->operator+=(newDir);

					// Update the current directory
					if(currentDir->find(component + '/'))
						currentDir = dynamic_cast<Directory*>(currentDir->find(component + '/'));

					delete newDir;
				}
			}

			if (contents.empty()) {
				File* newFile = new File(pathComp.back());
				newFile->update_parent_path(m_current->name());
				m_root->operator+=(newFile);
				delete newFile;
			}
			else {
				File* newFile = new File(pathComp.back(), contents);
				newFile->update_parent_path(m_current->name());
				m_root->operator+=(newFile);
				delete[] newFile;
			}
		}

	}

	// Add received resource to m_current.
	Filesystem& Filesystem::operator+=(Resource* resource)
	{
		*m_current += resource;
		return *this;
	}

	// Change the m_current directory to recieved directory.
	Directory* Filesystem::change_directory(const std::string& dir)
	{
		// If received directory is empty, then set m_current directory to root directory
		if (dir.empty())
			m_current = m_root;
		else {
			// If the received directory is exist, then update m_current directory to that directory.
			if (m_current->find(dir)) {
				m_current = dynamic_cast<Directory*>(m_current->find(dir));
			}
			// Otherwise thrown invalid_argument
			else {
				throw std::invalid_argument("Cannot change directory! " + dir + " not found!");
			}
		}
		return m_current;
	}

	// Return m_current.
	Directory* Filesystem::get_current_directory() const
	{
		return m_current;
	}

	// Deallocate m_root.
	Filesystem::~Filesystem()
	{
		delete m_root;
	}

	// Move constructor.
	Filesystem::Filesystem(Filesystem&& other)
	{
		// Move resources
		m_root = other.m_root;
		m_current = other.m_current;
		other.m_root = nullptr;
		other.m_current = nullptr;
	}

	// Move assignment operator.
	Filesystem& Filesystem::operator=(Filesystem&& other)
	{
		// Check self assignment
		if (this != &other) {

			// Cleanup current object
			delete m_root;

			// Move resources
			m_root = other.m_root;
			m_current = other.m_current;
			other.m_root = nullptr;
			other.m_current = nullptr;
		}
		return *this;
	}
}