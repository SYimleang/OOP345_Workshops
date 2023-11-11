// Workshop 7 - STL Algorithms
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 11, 2023

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
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
	void CovidCollection::display(std::ostream& out, const std::string& country) const {
		
		if(country != "ALL")
			out << "Displaying information of country = " << country << std::endl;

		// Summary value of "m_numCase"
		size_t totalWorldCases = std::accumulate(m_collection.begin(), m_collection.end(), (size_t)0, [](const size_t& totalWorldCases, const Covid& covid)
			{
				return totalWorldCases + covid.m_numCase;
			});

		// Summary value of "m_numDeath"
		size_t totalWorldDeaths = std::accumulate(m_collection.begin(), m_collection.end(), (size_t)0, [](const size_t& totalWorldDeaths, const Covid& covid)
			{
				return totalWorldDeaths + covid.m_numDeath;
			});

		// If country is "ALL" then sum all "m_numCase" and "m_numDeath"
		if (country == "ALL") {
			
			// Loop all elements to insert ostream.
			std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& covid) {
				out << covid << std::endl;
				});

			// Insert the conclusion
			out << "| " << std::setw(79) << "Total cases around the world: " << totalWorldCases << " |" << std::endl;
			out << "| " << std::setw(79) << "Total deaths around the world: " << totalWorldDeaths << " |" << std::endl;
		}
		// Otherwise, sum all "m_numCase" and "m_numDeath" of that country
		else {

			size_t totalCases = 0;
			size_t totalDeaths = 0;

			// Summary value of "m_numCase" and "m_numDeath". And insert all element in speccific coountry to ostream
			std::for_each(m_collection.begin(), m_collection.end(), [&totalCases, &totalDeaths, &country, &out](const Covid& covid) {
				if (covid.m_country == country) {
					totalCases += covid.m_numCase;
					totalDeaths += covid.m_numDeath;
					out << covid << std::endl;
				}
				});

			// Calculate percentages
			double casePercentage = (static_cast<double>(totalCases) / totalWorldCases) * 100.0;
			double deathPercentage = (static_cast<double>(totalDeaths) / totalWorldDeaths) * 100.0;

			// Define string for display as format
			std::string caseToDisplay = "Total cases in " + country;
			std::string deathToDisplay = "Total deaths in " + country;

			// Insert the conclusion
			out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
			out << "| " << std::right << std::setw(78) << caseToDisplay << ": " << std::setw(4) << totalCases << " |" << std::endl;
			out << "| " << std::right << std::setw(78) << deathToDisplay << ": " << std::setw(4) << totalDeaths << " |" << std::endl;
			out << "| " << std::right << std::setw(23) << country << " has " << std::fixed << std::setprecision(6) << casePercentage << "% of global cases and " << deathPercentage << "% of global deaths |" << std::endl;
		}
	}

	// Sort the collection of Covid objects in ascending order based on field.
	void CovidCollection::sort(const std::string& field)
	{
		// Calls sort algorithm.
		std::sort(m_collection.begin(), m_collection.end(), [field](const Covid& covid, const Covid& covidOther)
			{					
				// Checks if field is "country" or "DEFAULT", then sort by "m_country". 
				if (field == "country" || field == "DEFAULT") {
					// If values are equal then checks be "m_numDeath"
					if (covid.m_country == covidOther.m_country)
						return covid.m_numDeath < covidOther.m_numDeath;
					return covid.m_country < covidOther.m_country;
				}

				// Checks if field is "year", then sort by "m_year"
				else if (field == "year") {
					// If values are equal then checks be "m_numDeath"
					if (covid.m_year == covidOther.m_year)
						return covid.m_numDeath < covidOther.m_numDeath;
					return covid.m_year < covidOther.m_year;
				}
					
				// Checks if field is "variant", then sort by "m_variant"
				else if (field == "variant") {
					// If values are equal then checks be "m_numDeath"
					if (covid.m_variant == covidOther.m_variant)
						return covid.m_numDeath < covidOther.m_numDeath;
					return covid.m_variant < covidOther.m_variant;
				}
				else {
					return false;
				}
			});
	}

	// Return true if an object exists in the collection with the conditions, false otherwise.
	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		// Checks collections to find the matches object. Search in the collection for a city in the "country" where the variant has caused more deaths.
		return std::any_of(m_collection.begin(), m_collection.end(), [&](const Covid& covid) {
			return (covid.m_country == country) && (covid.m_variant == variant) && (covid.m_numDeath > deaths);
			});
	}

	// Create and return a collection of Covid that "m_numDeath"  more than received value.
	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		std::list<Covid> result;
		std::copy_if(m_collection.begin(), m_collection.end(), std::back_inserter(result), [&](const Covid& covid) {
			return covid.m_numDeath >= deaths;
			});
		return result;
	}

	// Update "m_status" of each city
	void CovidCollection::updateStatus() {
		// Loop all cities
		std::for_each(m_collection.begin(), m_collection.end(), [](Covid& covid) {
			// Check conditions for an update 
			if (covid.m_numDeath > 300)
				covid.m_status = "EPIDEMIC";
			else if (covid.m_numDeath < 50)
				covid.m_status = "EARLY";
			else
				covid.m_status = "MILD";
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
			<< " | " << std::setw(3) << theCovid.m_numDeath << " |"
			<< " | " << std::right << std::setw(8) << theCovid.m_status << " |";

		return out;
	}
}

