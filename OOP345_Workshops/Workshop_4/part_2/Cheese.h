// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>

namespace sdds {
	class Cheese {
		std::string m_name{};		// The name (a string): the name of the cheese.
		int m_weight{};				// The weight (an integer): the weight/amount in grams of the cheese.
		double m_price{};			// The price (a floating-point number in double precision): the price per gram of the cheese.
		std::string m_features;		// The features (a string): a description of the features/qualities of the cheese.

	public:
		// Default constructor.
		Cheese() : m_name("NaC") {};

		// This constructor is responsible for extracting information about the cheese 
		// from the string and storing the tokens in the instance's attributes.
		Cheese(const std::string& str);

		// A modifier that receives as a parameter a weight/amount of cheese to slice from the current cheese object.
		Cheese slice(size_t weight);

		// Getter of m_weight.
		int getWeight() const;

		// Overload the insertion operator to insert the contents of a Cheese object into an ostream object in the format.
		friend std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
	};
	
}

#endif // !SDDS_CHEESE_H
