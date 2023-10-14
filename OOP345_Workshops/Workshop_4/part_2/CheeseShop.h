// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include "Cheese.h"

// Composition with Cheese
namespace sdds {
	class CheeseShop {
		std::string m_shopName{};		// The shope name (a string): the name of the shop.
		const Cheese** m_sCheeses{};	// A dynamically-allocated array of pointers to dynamically-allocated objects of type Cheese
		size_t m_cnt{};					// The counter to count the number of Cheese object in the shop.

	public:
		// A constructor that receives as a parameter the name of the shop. The default value for the parameter is "No Name".
		CheeseShop(const std::string& name = "No Name");

		// Rules of five
		~CheeseShop();
		CheeseShop(const CheeseShop&);
		CheeseShop& operator=(const CheeseShop&);
		CheeseShop(CheeseShop&&);
		CheeseShop& operator=(CheeseShop&&);

		// A modifier that adds a cheese object to the array of pointers.
		CheeseShop& addCheese(const Cheese&);

		// Overload the insertion operator to insert the content of a CheeseShop object into an ostream object.
		friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
	};
}
#endif // !SDDS_CHEESESHOP_H
