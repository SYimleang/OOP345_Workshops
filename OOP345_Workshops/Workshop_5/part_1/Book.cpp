// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/14

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Book.h"

namespace sdds {

	Book::Book(const std::string& strBook)
	{
		std::string input = strBook;

		// Use stringstream to tokenize the input.
		std::stringstream iss(input);
		std::string token;

		// Parsing token until found ',', delete ' ' from the front and back and assign to m_author.
		std::getline(iss, token, ',');
		while (!token.empty() && token.front() == ' ')
			token.erase(token.begin());
		while (!token.empty() && token.back() == ' ')
			token.pop_back();
		if (!token.empty())
			m_author = token;

		// Parsing token until found ',', delete ' ' from the front and back and assign to m_title.
		getline(iss, token, ',');
		while (!token.empty() && token.front() == ' ')
			token.erase(token.begin());
		while (!token.empty() && token.back() == ' ')
			token.pop_back();
		if (!token.empty())
			m_title = token;

		// Parsing token until found ',', delete ' ' from the front and back and assign to m_country.
		getline(iss, token, ',');
		while (!token.empty() && token.front() == ' ')
			token.erase(token.begin());
		while (!token.empty() && token.back() == ' ')
			token.pop_back();
		if (!token.empty())
			m_country = token;

		// Parsing token until found ',', delete ' ' from the front and back and assign to m_price by parse to double.
		getline(iss, token, ',');
		if (!token.empty())
			m_price = std::stod(token);

		// Parsing token until found ',', delete ' ' from the front and back and assign to m_year by parse to int.
		getline(iss, token, ',');
		if (!token.empty())
			m_year = std::stoi(token);

		// Parsing token until found '\n', delete ' ' from the front and back and assign to m_desc.
		getline(iss, token, '\n');
		while (!token.empty() && token.front() == ' ')
			token.erase(token.begin());
		while (!token.empty() && token.back() == ' ')
			token.pop_back();
		if (!token.empty())
			m_desc = token;
	}

	// Return m_title of the object.
	const std::string& Book::title() const
	{
		return m_title;
	}

	// Return m_country of the object.
	const std::string& Book::country() const
	{
		return m_country;
	}

	// Return m_year of the object.
	const size_t& Book::year() const
	{
		return m_year;
	}

	// Return m_price of the object by reference.
	double& Book::price()
	{
		return m_price;
	}

	// Display the Cheese object as the following format:
	/*
		AUTHOR | TITLE | COUNTRY | YEAR | PRICE | DESCRIPTION

		the author printed on a field of size 20;
		the title printed on a field of size 22;
		the country printed on a field of size 5;
		the year printed on a field of size 4;
		the price printed on a field of size 6, with 2 decimal digits;
	*/
	std::ostream& operator<<(std::ostream& os, const Book& book)
	{
		os << std::right << std::setw(20) << book.m_author
			<< " | " << std::right << std::setw(22) << book.m_title
			<< " | " << std::right << std::setw(5) << book.m_country
			<< " | " << std::right << std::setw(4) << book.m_year
			<< " | " << std::fixed << std::setprecision(2) << std::right << std::setw(6) << book.m_price
			<< " | " << std::left << book.m_desc;

		return os;
	}
}

