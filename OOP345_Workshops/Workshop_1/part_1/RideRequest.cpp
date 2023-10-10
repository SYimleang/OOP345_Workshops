// Workshop 1 - Linkage, Storage Duration, Namespaces, and OS Interface
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/15

#include <iostream>
#include <iomanip>
#include <string.h>
#include "RideRequest.h"

using namespace std;

namespace sdds {
	/* Constructor */
	RideRequest::RideRequest() : m_customerName{}, m_rideDetails{}, m_price{}, m_discount(false) {};

	/* Destructor */
	RideRequest::~RideRequest() {}

	/* Copy constructor */
	RideRequest::RideRequest(const RideRequest& other) 
	{
		*this = other;
	}

	/* Copy Assignment*/
	RideRequest& RideRequest::operator=(const RideRequest& other) 
	{
		// Self assignment check
		if (this != &other)
		{
			// Shallow copy
			m_price = other.m_price;
			m_discount = other.m_discount;

			// Deep copy
			for (int i = 0; i < 11; ++i)
				m_customerName[i] = other.m_customerName[i];
			for (int i = 0; i < 26; ++i)
				m_rideDetails[i] = other.m_rideDetails[i];
		}
		return *this;
	}

	/* read method. First check the istream condition, if istream condition is good 
	then read the data as a format and assign the values to each class member. */
	void RideRequest::read(istream& is) {
		char discount;
		m_discount = false;
		

		// Check if istream is in a good state.
		if (is.good())
		{
			// Read the data as a format (separated by ','
			is.getline(m_customerName, 11, ',');
			is.getline(m_rideDetails, 26, ',');
			is >> m_price;
			is.ignore(1, ',');		// Ignore ',' after read price
			is >> discount;
			
			// Check the discount status if read discount equal 'Y', then m_discount wil be true
			m_discount = (discount == 'Y');
		}
	}

	/* display method. Display the values of attributes of the object as a format. */
	void RideRequest::display() const {
		static int m_counter;			// Static integer that store counting number of the object
		double priceTaxed;
		double priceDiscounted;
		cout << setw(2) << left << ++m_counter << ". ";

		// Checks if customer name attribute is NULL, then will print the message.
		if (m_customerName[0] == '\0')
		{
			cout << "No Ride Request" << endl;
		}

		// If customer name attribute is not NULL, then will print the values as a format.
		else 
		{
			// Calculate the price plus tax
			priceTaxed = m_price * (1.0 + g_taxrate);
			// Calculate the price after deduct by discount, if no discount then will assign the priceTaxed
			if (m_discount)
				priceDiscounted = priceTaxed - g_discount;
			else
				priceDiscounted = priceTaxed;
			cout << setw(10) << left << m_customerName << "|"
				<< setw(25) << left << m_rideDetails << "|"
				<< fixed << setprecision(2) << setw(12) << left << priceTaxed << "|";
			if (m_discount)
				cout << setw(13) << right << priceDiscounted;
			cout << endl;
		}
	}
}
