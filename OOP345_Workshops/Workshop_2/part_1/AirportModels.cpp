// Workshop 2 - Move and Copy Semantics
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "AirportModels.h"

namespace sdds {

	/*
	=============
	Airport Class
	=============
	*/

	// Overload the insertion operator
	/* Output format:
		All labels will be aligned to the right, on a field of exactly 20 characters wide
		All values will be aligned to the left, on a field of exactly 30 characters wide
		the label is separated from the value by : (space-colon-space)
		the filling character is a dot (.)
	*/
	std::ostream& operator<<(std::ostream& os, const Airport& airport)
	{
		// Check if airport code is empty. If not empty, then print the values in a format.
		if (airport.m_code.empty()) {
			os << "Empty Airport";
		}
		else {
			os << std::setw(20) << std::right << std::setfill('.') << "Airport Code" << " : " << std::setw(30) << std::left << airport.m_code << std::endl;
			os << std::setw(20) << std::right << "Airport Name" << " : " << std::setw(30) << std::left << airport.m_name << std::endl;
			os << std::setw(20) << std::right << "City" << " : " << std::setw(30) << std::left << airport.m_city << std::endl;
			os << std::setw(20) << std::right << "State" << " : " << std::setw(30) << std::left << airport.m_state << std::endl;
			os << std::setw(20) << std::right << "Country" << " : " << std::setw(30) << std::left << airport.m_country << std::endl;
			os << std::setw(20) << std::right << "Latitude" << " : " << std::setw(30) << std::left << std::setfill('.') << airport.m_latitude << std::endl;
			os << std::setw(20) << std::right << "Longitude" << " : " << std::setw(30) << std::left << airport.m_longitude << std::setfill(' ') << std::endl;
		}
		return os;
	}

	/* 
	=================
	Airport Log Class
	=================
	*/

	// Constructor with filename parameter.
	AirportLog::AirportLog(const char* filename) : m_airport{ nullptr }
	{
		std::ifstream is = std::ifstream(filename, std::ios_base::in);
		std::string temp;
		size_t count = 0;
		if (!is.is_open())
			std::cout << "Error: Uable to open file" << std::endl;
		else
		{
			if (m_airport)
				delete[] m_airport;

			// Counting number of airport in the file.
			while (getline(is, temp) && !is.eof())
				++count;
			
			// Minus first line
			m_count = --count;

			// Allocate dynamic memory for the array of airports based on the number found
			m_airport = new Airport[m_count];

			// Reread the file from the beginning
			is.clear();
			is.seekg(0);

			// Skip header in the first line.
			std::getline(is, temp);

			// Read data from the file and assign to each airport.
			for (size_t i = 0; i < count; i++) {
				getline(is, m_airport[i].m_code, ',');
				getline(is, m_airport[i].m_name, ',');
				getline(is, m_airport[i].m_city, ',');
				getline(is, m_airport[i].m_state, ',');
				getline(is, m_airport[i].m_country, ',');
				is >> m_airport[i].m_latitude;
				is.ignore();
				is >> m_airport[i].m_longitude;
				is.ignore();

			}
		}
	}

	// Destructor
	AirportLog::~AirportLog() {
		if (m_airport != nullptr) {
			delete[] m_airport;
			m_airport = nullptr;
		}
	}

	// Copy constructor
	AirportLog::AirportLog(const AirportLog& other) {
		*this = other;
	}

	// Copy assignment operator
	AirportLog& AirportLog::operator=(const AirportLog& other) {
		// Check for self assignment.
		if (this != &other) {

			// Check if receives airportlog is empty
			if (other.m_count == 0) {
				m_count = 0;
				m_airport = nullptr;
				return *this;
			}

			// Cleanup current dynamic array of Airport 
			if (m_airport != nullptr) {
				delete[] m_airport;
			}

			// Copy number of airports. (Shallow copy)
			m_count = other.m_count;

			// Copy dynamic array of Airport. (Deep copy)
			m_airport = new Airport[m_count];
			for (size_t i = 0; i < m_count; i++) {
				m_airport[i] = other.m_airport[i];
			}
		}
		return *this;
	}

	// Move constructor
	AirportLog::AirportLog(AirportLog&& other) {
		*this = std::move(other);
	}

	// Move assignment operator
	AirportLog& AirportLog::operator=(AirportLog&& other)
	{
		// Check for self assignment.
		if (this != &other) {

			// Cleanup current dynamic array of Airport.
			if (m_airport != nullptr) {
				delete[] m_airport;
			}

			// Copy number of airports. (Shallow copy)
			m_count = other.m_count;
			other.m_count = 0;

			// Move the resource
			m_airport = other.m_airport;
			other.m_airport = nullptr;
		}
		return *this;
	}

	// Add airport to the log.
	void AirportLog::addAirport(const Airport& airport) {

		// Dynamic allocate temporary airport
		Airport* tempAirport = new Airport[m_count + 1];

		// Assign current airport to the temporary airport
		for (size_t i = 0; i < m_count; ++i) {
			tempAirport[i].m_code = m_airport[i].m_code;
			tempAirport[i].m_name = m_airport[i].m_name;
			tempAirport[i].m_city = m_airport[i].m_city;
			tempAirport[i].m_state = m_airport[i].m_state;
			tempAirport[i].m_country = m_airport[i].m_country;
			tempAirport[i].m_latitude = m_airport[i].m_latitude;
			tempAirport[i].m_longitude = m_airport[i].m_longitude;
		}

		// Assign received airport to temporary airport
		tempAirport[m_count].m_code = airport.m_code;
		tempAirport[m_count].m_name = airport.m_name;
		tempAirport[m_count].m_city = airport.m_city;
		tempAirport[m_count].m_state = airport.m_state;
		tempAirport[m_count].m_country = airport.m_country;
		tempAirport[m_count].m_latitude = airport.m_latitude;
		tempAirport[m_count].m_longitude = airport.m_longitude;

		// Cleanup current airport array
		delete[] m_airport;

		// Assign temporary airport to current airport array object
		m_airport = tempAirport;
		++m_count;
	}

	// Function to find the airport and return the all found airports
	AirportLog AirportLog::findAirport(std::string state, std::string country) const {
		static AirportLog result;
		result = {};
		for (size_t i = 0; i < m_count; ++i) {
			if (m_airport[i].m_state == state && m_airport[i].m_country == country) {
				result.addAirport(m_airport[i]);
			}
		}
		return result;
	}

	// Query index of current airport. And will 
	Airport AirportLog::operator[](size_t ndx) const {
		if (ndx >= m_count) {
			static Airport empty{};
			return empty;
		}
		return m_airport[ndx];
	}

	// Casting operator to return number of airport.
	AirportLog::operator size_t() const {
		return m_count;
	}
}