// Workshop 1 - Linkage, Storage Duration, Namespaces, and OS Interface
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/17

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

extern double g_taxrate;	// Global variables store the value of the tax rate as floating-point numbers in double precision
extern double g_discount;	// Global variables store the value of discount as floating-point numbers in double precision

namespace sdds {
	class RideRequest
	{
		char m_customerName[11]{};	// C-style null-terminated string in any length representing the name of the customer.
		char* m_rideDetails{};		// C-style null-terminated string in any length representing the extra details about the ride.
		double m_price;				// The price of the ride as a floating-point number in double precision.
		bool m_discount;			// Boolean flag indicating whether the ride receives a discount.
		
	public:
		RideRequest();										// Default constructor
		~RideRequest();										// Destructor
		RideRequest(const RideRequest& other);				// Copy cconstructor
		RideRequest& operator=(const RideRequest& other);	// Copy assignment

		void read(std::istream& is);	// Modifier that receives an istream reference.
		void display() const;			// Query that displays to the screen the content of an Ride Request instance in the format
	};
}

#endif
