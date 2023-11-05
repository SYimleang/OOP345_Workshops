#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Directory.h"

namespace sdds {
	// Update m_name of Resource parent class.
	Directory::Directory(const std::string& name) {
		// If the received parameter is not end with '/', then add '/' to the end of the m_name
		if (!name.empty() && name.back() != '/')
			m_name = name + '/';
		else
			m_name = name;
	}

	// Set and update m_parent_path from received parameter.
	void Directory::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
		// Update each resource to absolute path.
		for (Resource* resource : m_contents) {
			resource->update_parent_path(m_parent_path + m_name);
		}
	}

	// Return Flags::DIR.
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}

	// Return the absolute path of the file.
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}

	// Return m_name of the resource.
	std::string Directory::name() const
	{
		return m_name;
	}

	// Return the number of resource in current directory.
	int Directory::count() const
	{
		return static_cast<int>(m_contents.size());
	}

	// Return the summary of sizes of current directory.
	size_t Directory::size() const
	{
		return std::accumulate(m_contents.begin(), m_contents.end(), 0u, [](size_t total, const Resource* resource){ 
				return total + resource->size();
			});
	}

	// Add resource to the directory and return current directory.
	Directory& Directory::operator+=(Resource* resource)
	{
		// Looping all resources of m_contents
		for (Resource* r : m_contents) {
			// Checks if the name already contained in the m_contents
			if (r->name() == resource->name()) {
				throw "Resource with the same name already exists in the directory";
			}
		}
		// Update absolute path and add to the m_contents
		resource->update_parent_path(m_parent_path + m_name);
		m_contents.push_back(resource);
		return *this;
	}

	// Find and return the address of matching name.
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
	{
		// Search for resource's name that matches the received name parameter.
		auto it = std::find_if(m_contents.begin(), m_contents.end(), [&name](const Resource* resource) {
				return resource->name() == name;
			});

		// If the "it" is not the last value then return "it"
		if (it != m_contents.end()) {
			return *it;
		}

		// Flag optional condition
		// 
		if (flags.size() == 1 && flags[0] == OpFlags::RECURSIVE) {
			// Loop each resource in m_contents
			for (Resource* resource : m_contents) {
				// Checks that type is the directory
				if (resource->type() == NodeType::DIR) {
					// Create a pointer that point to the directory
					Directory* dir = dynamic_cast<Directory*>(resource);
					// Checks that casting sucessful
					if (dir) {
						// Recursive this function
						Resource* foundResource = dir->find(name, { OpFlags::RECURSIVE });
						// Checks if the recursive called return the address then return the return address
						if (foundResource) {
							return foundResource;
						}
					}
				}
			}
		}

		// return nullptr if not found
		return nullptr;
	}
	
	// Destructor
	Directory::~Directory()
	{
		// Deallocate each resource
		for (Resource* resource : m_contents) {
			delete resource;
		}
	}
}

