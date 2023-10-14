// Workshop 3 - Templates
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/01

#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds {

    // Default constructor
    Book::Book() {}

    // Constructor with arguments to assign receives arguments to the object members.
    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}

    // Copy constructor.
    Book::Book(const Book& other)
    {
        *this = other;
    }

    // Copy assignment operator.
    Book& Book::operator=(const Book& other)
    {
        if (this != &other) {
            m_title = other.m_title;
            m_numChapters = other.m_numChapters;
            m_numPages = other.m_numPages;
        }
        return *this;
    }

    // Move constructor.
    Book::Book(Book&& other)
    {
        *this = std::move(other);
    }

    // Move assignment operator.
    Book& Book::operator=(Book&& other)
    {
        if (this != &other) {
            m_numChapters = other.m_numChapters;
            m_numPages = other.m_numPages;
            m_title = other.m_title;

            other.m_title = "";
            other.m_numChapters = 0;
            other.m_numChapters = 0;
        }
        return *this;
    }

    // Comparing the pages per chapter of each Book object.
    bool Book::operator<(const Book& other) const {
        //  If Book object on the left is less than the right, then return true.
        return ((double)(m_numPages) / m_numChapters) <
            ((double)(other.m_numPages) / other.m_numChapters);
    }

    // Comparing the pages per chapter of each Book object.
    bool Book::operator>(const Book& other) const {
        //  If Book object on the left is more than the right, then return true.
        return other < *this;
    }

    // Print method to print the date of Book object as a format.
    std::ostream& Book::print(std::ostream& os) const {

        // Validation condition for print the output. (the title is not empty 
        // (has at least one character), it has at least one chapter, and it has at least one page.)
        if (!m_title.empty() && m_numChapters > 0 && m_numPages > 0) {
            os.setf(std::ios::right); os.setf(std::ios::fixed);
            os.width(m_numChapters > 9 ? 49 : 50);
            os << m_title << ',' << m_numChapters << ',' << m_numPages << " | (";

            os.precision(6);
            os << (double)m_numPages / m_numChapters << ")    ";

            os.unsetf(std::ios::right);
        }

        // If this is invalid then display error message.
        else {
            os << "| Invalid book data";
        }
        return os;
    }

    // Overload the '<<' operator to print a Book object.
    std::ostream& operator<<(std::ostream& os, const Book& bk) {
        return bk.print(os);
    }
}