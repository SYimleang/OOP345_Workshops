// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>
#include <string>

namespace sdds
{
    class Movie
    {
        std::string m_title;    // The title of the movie
        size_t m_year;          // The year of release of the movie
        std::string m_desc;     // The description of the movie

    public:
        // A default constructor
        Movie();

        // A query that returns the title of the movie
        const std::string& title() const;

        // Receives the movie through a reference to a string. 
        // This constructor extracts the information about the movie from the string and stores the tokens in the attributes.
        Movie(const std::string& strMovie);

        // A templated function. 
        // This function calls the overloaded operator() on instance spellChecker, passing to it the movie title and description
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_desc);
        }

        // Overload the insertion operator to insert the content of a movie object into an ostream object.
        friend std::ostream& operator<<(std::ostream& os, const Movie& src);
    };
}
#endif // !SDDS_MOVIE_H