// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Cheese.h"

class Cheese;

namespace sdds {

	// A constructor to read the received string and assign to the Cheese objects.
	Cheese::Cheese(const std::string& str)
	{
		// Set the object to empty state.
		m_weight = 0;
		m_price = 0.0;

		// Parse the input string.
		std::istringstream iss(str);
		std::string token;

		// Extract the name tokens using ',' as the delimiter.
		std::getline(iss, token, ',');
		if (!token.empty()) {

			// Remove leading and trailing spaces from each name.
			while (!token.empty() && token.front() == ' ')
				token.erase(token.begin());
			while (!token.empty() && token.back() == ' ')
				token.pop_back();

			if (!token.empty())
				m_name = token;
		}

		// Extract the weight tokens using ',' as the delimiter. Then set to an object by convert string to int.
		std::getline(iss, token, ',');
		if (!token.empty()) 
			m_weight = std::stoi(token);

		// Extract the price tokens using ',' as the delimiter. Then set to an object by convert string to double.
		std::getline(iss, token, ',');
		if (!token.empty()) 
			m_price = std::stod(token);

		// Extract the feature tokens using ',' as the delimiter.
		while (std::getline(iss, token, ',')) {
			if (!token.empty()) {

				// Remove leading and trailing spaces from each feature
				while (!token.empty() && token.front() == ' ')
					token.erase(token.begin());
				while (!token.empty() && token.back() == ' ')
					token.pop_back();

				// Insert space between each word.
				if (!token.empty()) {
					m_features += token + ' ';
				}
			}
		}
	}

	// Return m_wieght
	int Cheese::getWeight() const
	{
		return m_weight;
	}

	// The modifier to reduce the weight of the Cheese object.
	Cheese Cheese::slice(size_t weight)
	{
		// Create the copy object of the current Cheese object for modify.
		Cheese slicedCheese = *this;

		// Check if there is enough cheese to make this slice. Then decrease the object weight by received value.
		if (weight <= (size_t)(m_weight)) {
			slicedCheese.m_weight = (int)(weight);
			this->m_weight -= weight;
		}

		// If there isn't enough cheese, then return a cheese object that is in an empty state instead.
		else {
			slicedCheese.m_name = "NaC";
			slicedCheese.m_weight = 0;
			slicedCheese.m_price = 0.0;
			slicedCheese.m_features = "";
		}
		return slicedCheese;
	}

	// Display the Cheese object as the following format:
	/*	
	A vertical bar "|", The name of the cheese in left alignment and a field width of 21
	A vertical bar "|", The weight of the cheese with a field width of 5
	A vertical bar "|", The price of the cheese in fixed format, 2 decimal place precision and a field width of 5
	A vertical bar "|", The features of the cheese in right alignment and a field width of 34
	A vertical bar "|", A newline
	*/
	std::ostream& operator<<(std::ostream& os, const Cheese& cheese)
	{
		os << "|" << std::left << std::setw(21) << cheese.m_name 
			<< "|" << std::setw(5) << cheese.m_weight 
			<< "|" << std::fixed << std::setprecision(2) << std::setw(5) << cheese.m_price
			<< "|" << std::right << std::setw(34) << cheese.m_features 
			<< "|" << std::endl;

		return os;
	}

}
