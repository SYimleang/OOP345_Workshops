// Workshop 4 - Containers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/08

#include "CheeseShop.h"

namespace sdds {

	// Constructor to set the m_shopName to the received string.
	CheeseShop::CheeseShop(const std::string& name) : m_sCheeses(nullptr), m_cnt(0)
	{
		m_shopName = name;
	}

	// Destructor.
	CheeseShop::~CheeseShop()
	{
		for (size_t i = 0; i < m_cnt; ++i)
			delete m_sCheeses[i];
		delete[] m_sCheeses;
	}

	// Copy construction.
	CheeseShop::CheeseShop(const CheeseShop& other)
	{
		*this = other;
	}

	// Copy assignment operator.
	CheeseShop& CheeseShop::operator=(const CheeseShop& other)
	{
		// Self assignment checks.
		if (this != &other) {

			// Cleanup current object.
			for (size_t i = 0; i < m_cnt; ++i)
				delete m_sCheeses[i];
			delete[] m_sCheeses;

			// Shallow copy.
			m_shopName = other.m_shopName;
			m_cnt = other.m_cnt;

			// Deep copy.
			m_sCheeses = new const Cheese*[m_cnt]; //const Cheeses**
			for (auto i = 0u; i < m_cnt; ++i)
				m_sCheeses[i] = new Cheese(*(other.m_sCheeses[i]));
		}
		return *this;
	}

	// Move construction.
	CheeseShop::CheeseShop(CheeseShop&& other)
	{
		*this = std::move(other);
	}

	// Move assignment operator.
	CheeseShop& CheeseShop::operator=(CheeseShop&& other)
	{
		// Self assignment checks.
		if (this != &other) {

			// Cleanup current object.
			for (size_t i = 0; i < m_cnt; ++i)
				delete m_sCheeses[i];
			delete[] m_sCheeses;

			// Shallow copy.
			m_shopName = other.m_shopName;
			m_cnt = other.m_cnt;
			other.m_shopName = "";
			other.m_cnt = 0;

			// Move the resource.
			m_sCheeses = other.m_sCheeses;
			other.m_sCheeses = nullptr;
		}
		return *this;
	}

	// Add the Cheese object to the CheeseShop object.
	CheeseShop& CheeseShop::addCheese(const Cheese& newCheese)
	{
		// Create temporary object pointer to hold the current object pointer (m_sCheeses).
		const Cheese** cheesesTemp = new const Cheese* [m_cnt + 1];
		for (size_t i = 0; i < m_cnt; ++i)
			cheesesTemp[i] = m_sCheeses[i];

		// Add received argument to the temporary object pointer.
		cheesesTemp[m_cnt] = new Cheese(newCheese);

		// Cleanup current object pointer (m_sCheeses).
		delete[] m_sCheeses;

		// Set current object pointer (m_sCheeses) to the temporary object pointer.
		m_sCheeses = cheesesTemp;
		++m_cnt;

		return *this;
	}

	// Overload '<<' operator to display the shop's name and cheese in the inventory.
	std::ostream& operator<<(std::ostream& os, const CheeseShop& shop)
	{
		// Add shopname output to the ostream.
		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;
		os << shop.m_shopName << std::endl;
		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;

		// If no Cheese object in the CheeseShop object.
		if (shop.m_cnt == 0) {
			os << "This shop is out of cheese!" << std::endl;

		}

		// If there are Cheese objects in the CheeseShop object, then add output of cheese to the ostream.
		else {
			for (size_t i = 0; i < shop.m_cnt; ++i) {
				os << *shop.m_sCheeses[i];
			}
		}

		for (auto i = 0u; i < 26; ++i)
			os << "-";
		os << std::endl;

		return os;
	}
}
