// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include "Cheese.h"

// Aggregation with Cheese
namespace sdds {
	class CheeseParty {
		const Cheese** m_pCheeses{};	// A dynamically-allocated array of pointers to objects of type Cheese.
		size_t m_cnt{};					// The counter to count the number of Cheese object in the party.
		size_t m_capacity{};

	public:
		CheeseParty();

		// Rules of five
		~CheeseParty();
		CheeseParty(const CheeseParty&);
		CheeseParty& operator=(const CheeseParty&);
		CheeseParty(CheeseParty&&);
		CheeseParty& operator=(CheeseParty&&);

		// A modifier that adds a cheese object to the array of pointers.
		CheeseParty& addCheese(const Cheese&);

		// A modifier that removes any cheeses from the array that have a 0 weight.
		CheeseParty& removeCheese();

		// Overload the insertion operator to insert the content of a CheeseParty object into an ostream object
		friend std::ostream& operator<<(std::ostream& os, const CheeseParty& party);
	};
}
#endif // !SDDS_CHEESEPARTY_H 
