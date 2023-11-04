#include "Directory.h"

namespace sdds {
	// Update m_name of Resource parent class.
	Directory::Directory(const std::string& name) {
		if (!name.empty() && name.back() != '/')
			m_name = name + '/';
		else
			m_name = name;
	}

	// 
	void Directory::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
		for (Resource* resource : m_contents) {
			resource->update_parent_path(m_parent_path + m_name);
		}
	}
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}

	// Return m_name of the resource
	std::string Directory::name() const
	{
		return m_name;
	}
	int Directory::count() const
	{
		return static_cast<int>(m_contents.size());
	}

	// Return size 
	size_t Directory::size() const
	{
		size_t totalSize = 0;
		for (Resource* resource : m_contents) {
			totalSize += resource->size();
		}
		return totalSize;
	}


	Directory& Directory::operator+=(Resource* resource)
	{
		for (Resource* r : m_contents) {
			if (r->name() == resource->name()) {
				throw "Resource with the same name already exists in the directory";
			}
		}
		resource->update_parent_path(m_parent_path + m_name);
		m_contents.push_back(resource);
		return *this;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
	{
		for (Resource* resource : m_contents) {
			if (resource->name() == name) {
				return resource;
			}
		}

		if (flags.size() == 1 && flags[0] == OpFlags::RECURSIVE) {
			for (Resource* resource : m_contents) {
				if (resource->type() == NodeType::DIR) {
					Directory* dir = dynamic_cast<Directory*>(resource);
					if (dir) {
						Resource* foundResource = dir->find(name, { OpFlags::RECURSIVE });
						if (foundResource) {
							return foundResource;
						}
					}
				}
			}
		}

		return nullptr;
	}
	
	// Destructor
	Directory::~Directory()
	{
		for (Resource* resource : m_contents) {
			delete resource;
		}
	}
}

