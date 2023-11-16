// Workshop 8 - Smart Pointers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 16, 2023

#ifndef SDDS_PROFILE_H
#define SDDS_PROFILE_H

#include <iomanip>
#include <string>
#include <fstream>

namespace sdds {

	const int Address_postal_code_length = 7;

	// The Address structure
	struct Address {
		unsigned number;		// The street number.
		std::string street;		// The street name
		std::string postal_code;// The postal code

		// The function that load the address information from the file
		bool load(std::ifstream& f) {
			f >> number >> street;
			char postal_code_temp[1 + Address_postal_code_length + 1] = { 0 };
			f.read(postal_code_temp, Address_postal_code_length + 1);
			postal_code = std::string(postal_code_temp + 1);
			return f.good();
		}

		// Helper overload insertion operator. Insert the address information to the ostream
		friend std::ostream& operator<<(std::ostream& os, const Address& ad) {
			os << std::setw(10) << ad.number << " " 
				<< std::setw(10) <<  ad.street << " "
				<< std::setw(7) << ad.postal_code;
			return os;
		}
	};

	// The Name structure
	struct Name {
		std::string first_name;	// The first name of the profile
		std::string last_name;	// The last name of the profile.

		// The function that load the name of the profile from the file
		bool load(std::ifstream& f) {
			f >> first_name >> last_name;
			return f.good();
		}

		// Helper overload insertion operator. Insert the name of the profile to the ostream
		friend std::ostream& operator<<(std::ostream& os, const Name& n) {
			os << std::setw(10) << n.first_name << std::setw(10) << n.last_name;
			return os;
		}
	};

	// The Profile structure
	struct Profile {
		static int m_idGenerator;	// ID generator of the profile
		int m_id{++m_idGenerator};	// ID of the profile
		Name m_name;				// Name of the profile
		Address m_address;			// Address of the profile
		unsigned m_age;				// Age of the profile
		// this variable is used to print trace messages from
		//     constructors/destructor
		static bool Trace;

		// Default constructor
		Profile() = default;

		// Function to load the profile information from the file
		bool load(std::ifstream& f) {
			m_name.load(f);
			m_address.load(f);
			f >> m_age;
			return f.good();
		}

		// Constructor with three arguments. Assign the received parameter to "m_name", "m_address" and "m_age", then 
		Profile(const Name& name, const Address& addr, unsigned age) {
			this->m_name = name;
			this->m_address = addr;
			this->m_age = age;
			if (Profile::Trace)
				std::cout << "     C [" << m_id << "][" << this->m_name << "]" << std::endl;
		}

		// Copy constructor.
		Profile(const Profile& other) {
			this->m_name = other.m_name;
			this->m_address = other.m_address;
			this->m_age = other.m_age;
			// we add this constructor for tracing messages
			if (Profile::Trace)
				std::cout << "    CC [" << m_id << "][" << m_name << "] copy of [" << other.m_id << "]\n";
		}

		// Destructor. Display the destruction message
		~Profile() {
			if (Profile::Trace)
				std::cout << "    ~D [" << m_id << "][" << this->m_name << "]" << std::endl;
		}

		// Function to validate the address
		void validateAddress() const {

			// Validate the postal code as a format like "ANA NAN" and the address's number is positive number
			if (m_address.number < 0 ||												// Check the negative number
				m_address.postal_code.length() != Address_postal_code_length ||		// Check length of the postal code
				!std::isalpha(m_address.postal_code[0]) ||							// Check first character	(alphabet)
				!std::isdigit(m_address.postal_code[1]) ||							// Check second character	(digit)
				!std::isalpha(m_address.postal_code[2]) ||							// Check third character	(alphabet)
				!std::isspace(m_address.postal_code[3]) ||							// Check fourth character	(space)
				!std::isdigit(m_address.postal_code[4]) ||							// Check fifth character	(digit)
				!std::isalpha(m_address.postal_code[5]) ||							// Check sixth character	(alphabet)
				!std::isdigit(m_address.postal_code[6])) {							// Check seventh character	(digit)
					throw std::string("*** Invalid Address ***");
			}
		}

		// Helper overload insertion operator. Insert the profile information to the ostream.
		friend std::ostream& operator<<(std::ostream& os, const Profile& p) {
			os << std::setw( 5) << p.m_id
			   << std::setw(10) << p.m_name
			   << std::setw(10) << p.m_address
			   << std::setw( 5) << p.m_age;
			return os << std::endl;
		}

	};
	inline int Profile::m_idGenerator{};
	
}
#endif
