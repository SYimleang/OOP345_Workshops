// Workshop 3 - Templates
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/01

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds {
	class Book
	{
		std::string m_title{};		// String variable to hold the title of the Book object.
		unsigned m_numChapters{};	// Unsigned variable to hold the number of chapters in the Book object.
		unsigned m_numPages{};		// Unsigned variable to hold the number of pages in the Book object.
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);

		// Rules of five
		~Book() {};
		Book(const Book&);
		Book& operator=(const Book&);
		Book(Book&&);
		Book& operator=(Book&&);

		// Overload the '<' operator to compareing Book objects based on pages to chapter. 
		// Return true if the Book object on the left is less than the right.
		bool operator<(const Book&) const;

		// Overload the '>' operator to compareing Book objects based on pages to chapter. 
		// Return true if the Book object on the left is more than the right.
		bool operator>(const Book&) const;

		// Output the value of Book object.
		std::ostream& print(std::ostream& os) const;
	};

	// Overload '<<' operator to call print method in Book object.
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}
#endif
