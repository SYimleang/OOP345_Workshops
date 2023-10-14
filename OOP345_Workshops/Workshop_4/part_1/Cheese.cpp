#include <iostream>
#include <sstream>
#include <iomanip>
#include "Cheese.h"


class Cheese;

namespace sdds {

	Cheese::Cheese(const std::string& str)
	{
		m_name = "";
		m_weight = 0;
		m_price = 0.0;
		m_features = "";

		// Parse the input string.
		std::istringstream iss(str);
		std::string token;

		// Extract tokens using ',' as the delimiter
		std::getline(iss, token, ',');
		if (!token.empty()) {
			// Remove leading and trailing spaces from each feature
			while (!token.empty() && token.front() == ' ')
				token.erase(token.begin());
			while (!token.empty() && token.back() == ' ')
				token.pop_back();
			if (!token.empty())
				m_name += token;
		}

		std::getline(iss, token, ',');
		if (!token.empty()) 
			m_weight = std::stoi(token);

		std::getline(iss, token, ',');
		if (!token.empty()) 
			m_price = std::stod(token);

		// Extract features
		while (std::getline(iss, token, ',')) {
			if (!token.empty()) {
				// Remove leading and trailing spaces from each feature
				while (!token.empty() && token.front() == ' ')
					token.erase(token.begin());
				while (!token.empty() && token.back() == ' ')
					token.pop_back();
				if (!token.empty())
					m_features += token + ' ';
			}
		}
	}

	Cheese Cheese::slice(size_t weight)
	{
		Cheese slicedCheese = *this;

		if (weight <= (size_t)(m_weight)) {
			slicedCheese.m_weight = (int)(weight);
			this->m_weight -= weight;
		}
		else {
			slicedCheese.m_name = "NaC"; // Empty state
			slicedCheese.m_weight = 0;
			slicedCheese.m_price = 0.0;
			slicedCheese.m_features = "";
		}
		return slicedCheese;
	}

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
