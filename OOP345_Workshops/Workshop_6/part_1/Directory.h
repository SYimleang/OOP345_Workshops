#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <iostream>
#include <vector>
#include "Resource.h"

namespace sdds
{
	class Directory : public Resource {
		std::vector<Resource*> m_contents;
	public:
		// A custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
		Directory(const std::string&);

		// Sets the parent path to the parameter. For each resource that this directory holds, 
		// this member should also set their absolute path locations to the full absolute path of this directory.
		void update_parent_path(const std::string&) override;

		// A query that returns Flags::DIR.
		NodeType type() const override;

		// A query that returns the full absolute path of the directory (a concatenation of the absolute path location and the directory name).
		std::string path() const override;

		// A query that returns the name of the directory.
		std::string name() const override;

		// A query that returns the number of resources that this directory holds.
		int count() const override;

		// a query that returns the size of the directory in bytes. 
		// The size of the directory is the sum of the individual sizes of each resource that this directory holds. 
		// This member returns 0u if the directory is empty.
		size_t size() const override;

		/*
		Adds a resource to the directory and returns a reference to the current directory. 
		This member should check for existing resources in the directory with the same name:
			- if a match is found, throw and exception and do nothing else;
			- if no match is found, add the resource and update the absolute path location of the added resource with the directory's full absolute path.
		*/
		Directory& operator+=(Resource*);

		/*
		Finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found. 
		This member also takes an optional vector of flags that determine how the find is performed (defaults to an empty collection).
			- if the RECURSIVE flag is in the second parameter, this member will also attempt to recursively find 
			a match in each directory that is in the m_contents vector. 
		*/
		Resource* find(const std::string&, const std::vector<OpFlags>& flags = {});

		//Rules of five
		~Directory();										// A destructor that deallocates memory for each resource that this directory holds.
		Directory(const Directory&) = delete;				// Prevent from copy constructor.
		Directory& operator=(const Directory&) = delete;	// Prevent from copy assignment operator.
		Directory(Directory&&) = delete;					// Prevent from move constructor.
		Directory& operator=(Directory&&) = delete;			// Prevent from move assignment operator.
	};
}
#endif //!SDDS_DIRECTORY_H
