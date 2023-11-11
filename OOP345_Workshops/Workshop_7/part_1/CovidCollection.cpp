// Workshop 7 - STL Algorithms
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 10, 2023

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "CovidCollection.h"

namespace sdds {

	// Constructor with file name argument.
	CovidCollection::CovidCollection(const char* fileName)
	{
		// Open the received file
		std::fstream file(fileName);

		// Check if the file opened properly
		if(file){
			// Loop all line of the file
			while (file) {
				Covid covidCase;	// An object to hold covid information of each line
				std::string line;	// Token for extract each line
				// Check if line is not empty and get contents of each line
				if (std::getline(file, line)) {

					// Extract data to an object
					// each field has a fixed size: COUNTRY, CITY and VARIANT have exactly 25 characters
					covidCase.m_country = line.substr(0, 25);
					covidCase.m_city = line.substr(25, 25);
					covidCase.m_variant = line.substr(50, 25);

					// each field has a fixed size: YEAR, CASES and DEATHS have exactly 5 characters.
					covidCase.m_year = std::stoi(line.substr(75, 5));
					covidCase.m_numCase = std::stoi(line.substr(80, 5));
					covidCase.m_numDeath = std::stoi(line.substr(85, 5));

					// Remove leading and trailing spaces from the m_country
					covidCase.m_country.erase(0, covidCase.m_country.find_first_not_of(" \t"));
					covidCase.m_country.erase(covidCase.m_country.find_last_not_of(" \t") + 1);
					// Remove leading and trailing spaces from the m_city
					covidCase.m_city.erase(0, covidCase.m_city.find_first_not_of(" \t"));
					covidCase.m_city.erase(covidCase.m_city.find_last_not_of(" \t") + 1);
					// Remove leading and trailing spaces from the m_variant
					covidCase.m_variant.erase(0, covidCase.m_variant.find_first_not_of(" \t"));
					covidCase.m_variant.erase(covidCase.m_variant.find_last_not_of(" \t") + 1);

					// Push data to the collection.
					m_collection.push_back(covidCase);
				}
			}
		}
	}

	// Display the information of collection
	void CovidCollection::display(std::ostream& out) const {
		
		// Loop all elements to insert output.
		std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& covid) {
				out << covid << std::endl;
			});
		
	}

	// Inserts an object content to the ostream as a format.
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {

		out << "| " << std::left << std::setw(21) << theCovid.m_country
			<< " | " << std::setw(15) << theCovid.m_city
			<< " | " << std::setw(20) << theCovid.m_variant
			<< " | " << std::right << std::setw(6);
		// Checks if m_year is invalid (less than 0), then print spaces
		if (theCovid.m_year < 0) {
			out << "  ";
		}
		else {
			out << theCovid.m_year;
		}
			out << " | " << std::setw(4) << theCovid.m_numCase
			<< " | " << std::setw(3) << theCovid.m_numDeath << " |";

		return out;
	}
}

