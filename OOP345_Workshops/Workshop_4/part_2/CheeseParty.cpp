// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#include <iostream>
#include "CheeseParty.h"

namespace sdds {

	// Default constructor
	CheeseParty::CheeseParty() :m_pCheeses(nullptr) {}

	// Destructor.
	CheeseParty::~CheeseParty()
	{
		delete[] m_pCheeses;
	}

	// Copy constructor.
	CheeseParty::CheeseParty(const CheeseParty& other)
	{
		*this = other;
	}

	// Copy assignment operator.
	CheeseParty& CheeseParty::operator=(const CheeseParty& other)
	{
		// Self assignment checks.
		if (this != &other) {

			// Cleanup
			delete[] m_pCheeses;

			// Shallow copy.
			m_cnt = other.m_cnt;

			// Deep copy.
			m_pCheeses = new Cheese const*[m_cnt];
			for (size_t i = 0u; i < m_cnt; ++i)
				m_pCheeses[i] = other.m_pCheeses[i];
		}
		return *this;
	}

	// Move constructor.
	CheeseParty::CheeseParty(CheeseParty&& other)
	{
		*this = std::move(other);
	}

	// Move assignment operator.
	CheeseParty& CheeseParty::operator=(CheeseParty&& other)
	{
		// Self assignment checks.
		if (this != &other) {

			// Cleanup
			delete[] m_pCheeses;

			// Shallow copy.
			m_cnt = other.m_cnt;
			other.m_cnt = 0;

			// Move the resource.
			m_pCheeses = other.m_pCheeses;
				other.m_pCheeses = nullptr;
		}
		return *this;
	}

	// Add the Cheese object to the CheeseParty object.
	CheeseParty& CheeseParty::addCheese(const Cheese& newCheese)
	{
		// Search in the array of already stored cheeses. If they are, do nothing.
		for (size_t i = 0; i < m_cnt; ++i) {
			if (m_pCheeses[i] == &newCheese) {
				return *this;
			}
		}

		// Resizes the array to make room for the parameter if necessary.
		if (m_cnt >= m_capacity) {
			const Cheese** cheesesTemp = new const Cheese*[m_capacity + 1];
			for (size_t i = 0; i < m_cnt; ++i)
				cheesesTemp[i] = m_pCheeses[i];
			
			// Cleanup current object pointer (m_pCheeses).
			delete[] m_pCheeses;

			// Set current object pointer (m_pCheeses) to the temporary object pointer.
			m_pCheeses = cheesesTemp;
			++m_capacity;
		}

		// Add the address of the cheese to the party
		m_pCheeses[m_cnt] = &newCheese;
		++m_cnt;
		return *this;
	}

	// Remove 0 weight cheese by search for 0 weight cheese object, then set to nullptr and update the object counter.
	CheeseParty& CheeseParty::removeCheese()
	{
		size_t objCnt = 0;

		// Searches the array for 0 weight cheeses.
		for (size_t i = 0; i < m_cnt; ++i)
		{
			// If weight of Cheese[i] is 0.
			if (m_pCheeses[i]->getWeight() == 0) {
				// Sets the pointer in the array to nullptr
				m_pCheeses[i] = nullptr;
			}

			// If weight of Cheese[i] is not 0. Then add Cheese[i] to new counter.
			else {
				m_pCheeses[objCnt] = m_pCheeses[i];
				++objCnt;
			}
		}
		// Update new object counter.
		m_cnt = objCnt;

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const CheeseParty& party)
	{
		// Add Title output to the ostream.
		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;
		os << "Cheese Party" << std::endl;
		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;

		// If no Cheese object in the CheeseParty object.
		if (party.m_cnt == 0) {
			os << "This party is just getting started!" << std::endl;
		}

		// If there are Cheese objects in the CheeseParty object, then add output of cheese to the ostream.
		else {
			for (size_t i = 0; i < party.m_cnt; ++i) {
				if (party.m_pCheeses[i] != nullptr) {
					os << *party.m_pCheeses[i];
				}
			}
		}

		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;

		return os;
	}

}

