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
    Book::Book() : m_title(""), m_numChapters(1), m_numPages(10000) {}

    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}

    bool Book::operator<(const Book& other) const {
        return (static_cast<double>(m_numPages) / m_numChapters) <
            (static_cast<double>(other.m_numPages) / other.m_numChapters);
    }

    bool Book::operator>(const Book& other) const {
        return (static_cast<double>(m_numPages) / m_numChapters) >
            (static_cast<double>(other.m_numPages) / other.m_numChapters);
    }

    std::ostream& Book::print(std::ostream& os) const {
        if (!m_title.empty() && m_numChapters != 0 && m_numPages != 0) {
            os.setf(std::ios::right); os.setf(std::ios::fixed);
            os.width(m_numChapters > 9 ? 49 : 50);
            os << m_title << ',' << m_numChapters << ',' << m_numPages << " | (";

            os.precision(6);
            os << (double)m_numPages / m_numChapters << ")    ";

            os.unsetf(std::ios::right);
        }
        else {
            os << "| Invalid book data";
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Book& bk) {
        return bk.print(os);
    }
}