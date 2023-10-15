// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

namespace sdds {
	class Book {
		std::string m_author{};	// A string variable to holds name of the author of the book.
		std::string m_title{};	// A string variable to holds the title of the book.
		std::string m_country{};// A string variable to holds the country of publication.
		size_t m_year{};			// An int variable to holds the year of publication.
		double m_price{};		// A double variable to holds the price of the book.
		std::string m_desc;		// A string variable to holds the description: a short summary of the book.
	public:
		// Default constructor.
		Book(){};

		// A constructor that receives a reference to an unmodifiable string that contains information about the book; 
		// this constructor extracts the information about the book from the string by parsing it and stores the tokens in the object's attributes. 
		Book(const std::string& strBook);

		// A query that returns the title of the book.
		const std::string& title() const;

		// A query that returns the publication country.
		const std::string& country() const;

		// A query that returns the publication year.
		const size_t& year() const;

		// A function that returns the price by reference, allowing the client code to update the price.
		double& price();

		// A function calls the overloaded operator() on the instance spellChecker, passing to it the book description.
		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_desc);
		}

		// Overload the insertion operator to insert the content of a book object into an ostream object.
		friend std::ostream& operator<<(std::ostream& os, const Book& book);
	};
}
#endif //!SDDS_BOOK_H
