// Workshop 7 - STL Algorithms
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 10, 2023

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <vector>

namespace sdds
{
	// Struct that store the information of covid details.
	struct Covid {
		std::string m_country;	// Country
		std::string m_city;		// City
		std::string m_variant;	// Variant
		int m_year;				// Year
		size_t m_numCase;		// Number of cases
		size_t m_numDeath;		// Number of deaths
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};	// The collection of Covid struct
	public:
		// Custom constructor with one argument. Load the data of the file into attributes all covid details.
		CovidCollection(const char* fileName);

		// Display function. Display the details of each collection.
		void display(std::ostream& out) const;
	};

	// Inserts one Covid object into the first parameter.
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif //!SDDS_COVIDCOLLECTION_H