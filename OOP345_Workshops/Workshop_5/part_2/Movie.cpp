// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#include <iostream>
#include <string>
#include <iomanip>
#include "Movie.h"
#include "SpellChecker.h"

namespace sdds {

    // Default constructor.
    Movie::Movie() :m_title{}, m_year{}, m_desc{} {  }

	// Constructor initialize movie.
    Movie::Movie(const std::string& strMovie) {

        // Check if received string is not empty.
        if (!strMovie.empty()) {

            // Create the token to hold the received string.
            std::string token = strMovie;
            int ndx = 0u;

            // Lambda function for removes all spaces from the beginning and end of any token in the string.
            auto removeSpace = [=](std::string& src) {
                if (src[0] == ' ')
                    src.erase(0, src.find_first_not_of(' '));
                else
                    src.erase(src.find_last_not_of(' ') + 1);
            };

            // Removes space and assign token to m_title 
            removeSpace(token);
            ndx = token.find(',');
            m_title = token.substr(0, ndx);
            removeSpace(m_title);

            // Delete string in the token until ','
            token.erase(0, ndx + 1);

            // Removes space and assign token to m_year 
            removeSpace(token);
            ndx = token.find(',');
            m_year = std::stoi(token.substr(0, ndx));

            // Delete string in the token until ','
            token.erase(0, ndx + 1);

            // Removes space and assign token to m_desc 
            removeSpace(token);
            removeSpace(token);
            m_desc = token;
        }
    }

	// Getter. Return title of the movie.
	const std::string& Movie::title() const {
		return m_title;
	}

    // insert the content of a movie object into an ostream object, in the following format:
    // TITLE | YEAR | DESCRIPTION
    //      The title printed on a field of size 40
    //      The year printed on a field of size 4
    std::ostream& operator<<(std::ostream& os, const Movie& src) {
        os << std::setw(40) << std::right << src.m_title << " | ";
        os << std::left << std::setw(4) << src.m_year << " | " << src.m_desc << std::endl;

        return os;
    }
}