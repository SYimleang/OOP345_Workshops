// Workshop 2 - Move and Copy Semantics
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/24

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <string>

namespace sdds {
	struct Airport {
		std::string m_code{};		// A string representing the Airport code
		std::string m_name{};		// A string representing the Airport name
		std::string m_city{};		// A string representing the Airport city
		std::string m_state{};		// A string representing the Airport state
		std::string m_country{};	// A string representing the Airport country
		double m_latitude{ 0 };		// A floating point number in double precision representing the latitude of the airport
		double m_longitude{ 0 };	// A floating point number in double precision representing the longitude of the airport
	};

	std::ostream& operator<<(std::ostream& os, const Airport& airport);	// Overload the insertion operator to output an Airport object to an output stream.

	class AirportLog {
		Airport* m_airport{ nullptr };		// Dynamic array object of Airport
		size_t m_count{ 0 };				// Number of airport.

	public:
		AirportLog() {};						// Default constructor
		AirportLog(const char* filename);	// One argument constructor receives a filename

		// Rules of five
		~AirportLog();
		AirportLog(const AirportLog& other);
		AirportLog& operator=(const AirportLog& other);
		AirportLog(AirportLog&& other) ;
		AirportLog& operator=(AirportLog&& other) ;

		/* AddAirport will attempt to append the parameter to the dynamic array of airports held by the current object. 
		Resize the array appropriately to accommodate the new object and avoid memory leaks. */
		void addAirport(const Airport& airport);

		/* A query that receives two strings as paramenters representing the state name and the country name and returns an AirportLog object.
		The returned object will contain all of the airports in that state and country. */
		AirportLog findAirport(std::string state, std::string country) const;

		/* A query that will return the Airport in the dynamic array at the index provided.
		If the index is not valid, return an empty Airport instead. */ 
		Airport operator[](size_t ndx) const;

		/* is a casting operator that will convert the current object to a size_t value. 
		The returned value is the number of airports held by the current object. */
		operator size_t() const;
	};
}

#endif // AIRPORTMODELS_H
