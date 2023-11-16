// Workshop 8 - Smart Pointers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 16, 2023

#ifndef SDDS_DATABASE_H
#define SDDS_DATABASE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	// Template class
    template <typename T>
    class DataBase {
		std::vector<T> database;	// Collection of records of people
	public:
		// Default constructor
		DataBase() { }

		// Constructor with one argument. Load the content from received file name.
		DataBase(const char* fn) {

			// Open the file
			std::ifstream file(fn);

			// Check if the file open properly
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(fn) + std::string(" ***");

			// Load the contents of the file
			while (file) {
				T e;
				try {
					if (e.load(file))
						database.push_back(T(e));
				}
				catch (...) {
					break;
				}
			}
		}

		// Overload call operator. Return the size of the collection.
		size_t size() const { return database.size(); }

		// Overload index operator. Return the specific element.
		const T& operator[](size_t i) const { return database[i]; }

		// Overload the += operator to the DataBase template with a raw pointer. Copies the object into the collection attribute.
		DataBase<T>& operator+=(const T* obj) {
			database.push_back(*obj);
			return *this;
		}

		// Display function. Insert each element of the collection incformation to the ostream
		void display(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : database)
				os << e;
        }
	};

	// Helper overload insertion operator.
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const DataBase<T>& db) {
		db.display(os);
		return os;
	}
}
#endif