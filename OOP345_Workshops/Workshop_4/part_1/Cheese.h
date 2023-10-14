#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>

namespace sdds {
	class Cheese {
		std::string m_name;			// The name (a string): the name of the cheese.
		int m_weight{};				// The weight (an integer): the weight/amount in grams of the cheese.
		double m_price{};			// The price (a floating-point number in double precision): the price per gram of the cheese.
		std::string m_features{};	// The features (a string): a description of the features/qualities of the cheese.
	public:
		// Default constructor.
		Cheese() : m_name("NaC") {};

		// This constructor is responsible for extracting information about the cheese 
		// from the string and storing the tokens in the instance's attributes.
		Cheese(const std::string& str);

		Cheese slice(size_t weight);

		const std::string& getName() const;
		int getWeight() const;
		double getPrice() const;
		const std::string& getFeatures() const;

		friend std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
	};
	
}

#endif // !SDDS_CHEESE_H
