// Workshop 1 - Linkage, Storage Duration, Namespaces, and OS Interface
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/17

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "RideRequest.h"

using namespace std;

double g_taxrate = 0.00;	// Initialize the tax rate value
double g_discount = 0.00;	// Initialize discount value

namespace sdds {
	
	static int m_counter;			// Static integer that store counting number of the object

	/* Constructor */
	RideRequest::RideRequest() : m_price{0.0}, m_discount {false} {};

	/* Destructor */
	RideRequest::~RideRequest() 
	{
		delete[] m_rideDetails;
	}

	/* Copy constructor */
	RideRequest::RideRequest(const RideRequest& other) 
	{
			*this = other;
	}

	/* Copy Assignment*/
	RideRequest& RideRequest::operator=(const RideRequest& other) 
	{
		// Check for self assignment
		if (this != &other)
		{
			// Cleanup
			delete[] m_rideDetails;

			// Shallow copy
			m_price = other.m_price;
			m_discount = other.m_discount;
			m_rideDetails = new char[strlen(other.m_rideDetails) + 1];
			for (size_t i = 0; i < strlen(other.m_customerName); ++i)
				m_customerName[i] = other.m_customerName[i];

			// Deep copy
			if (other.m_rideDetails)
			{
				for (size_t i = 0; i < strlen(other.m_rideDetails); ++i)
					m_rideDetails[i] = other.m_rideDetails[i];
				m_rideDetails[strlen(other.m_rideDetails)] = '\0';
			}
		}
		return *this;
	}

	/* read method. First check the istream condition, if istream condition is good 
	then read the data as a format and assign the values to each class member. */
	void RideRequest::read(istream& is) {
		string bufferDesc{};	// C-style null-terminated string buffer to hold the description content from istream.
		char discount;				// Character variable to hold discount status from istream.
		m_discount = false;			// Reset to false.
		
		// Check if istream is in a good state.
		if (is.good())
		{
			// Read the data as a format (seperated by ',')
			is.getline(m_customerName, 11, ',');
			getline(is, bufferDesc, ',');
			is >> m_price;
			is.ignore(1, ',');		// Ignore ',' after read price
			is >> discount;

			// Deallocate ride description
			delete[] m_rideDetails;

			// Deep copy the ride description from the buffer.
			m_rideDetails = new char[strlen(bufferDesc.c_str()) + 1];
			
			for (size_t i = 0; i < strlen(bufferDesc.c_str()); ++i)
				m_rideDetails[i] = bufferDesc[i];
			m_rideDetails[strlen(bufferDesc.c_str())] = '\0';
			
			// Check the discount status if read discount equal 'Y', then m_discount wil be true
			m_discount = (discount == 'Y');
		}
	}

	/* display method. Display the values of attributes of the object as a format. */
	void RideRequest::display() const {
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
