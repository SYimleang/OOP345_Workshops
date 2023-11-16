// Workshop 8 - Smart Pointers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 16, 2023

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	// Exclude first argument from second argument by raw pointers.
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		
		// Loop all first parameter objects (allProfiles)
		for (auto i = 0u; i < allProfiles.size(); ++i) {
			bool isBanned = false;

			// Loop all second parameter objects
			for (auto j = 0u; j < bannedProfiles.size() && !isBanned; ++j) {

				// Find the matches object
				if (allProfiles[i].m_age == bannedProfiles[j].m_age &&
					allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) {
					isBanned = true;
				}
			}

			// If matches object not found
			if (!isBanned) {

				// Dynamic allocating current object
				Profile* newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);

				try {
					// Validate address
					newProfile->validateAddress();

					// Add dynamic object to "result"
					result += newProfile;
				}
				catch (...) {
					// Deallocate dynamic object
					delete newProfile;

					throw;
				}

				// Deallocate dynamic object
				delete newProfile;
			}
		}
		// Return "result"
		return result;
	}

	// Exclude first argument from second argument by smart pointers.
	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;

		// Loop all first parameter objects (allProfiles)
		for (auto i = 0u; i < allProfiles.size(); ++i) {
			bool isBanned = false;

			// Loop all second parameter objects
			for (auto j = 0u; j < bannedProfiles.size() && !isBanned; ++j) {

				// Find the matches object
				if (allProfiles[i].m_age == bannedProfiles[j].m_age &&
					allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) {
					isBanned = true;
				}
			}

			// If matches object not found
			if (!isBanned) {

				// Define smart pointers of current object
				unique_ptr<Profile> newProfile(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

				// Validate address
				newProfile->validateAddress();

				// Add current object to "result"
				result += newProfile;
			}
		}

		// Return "result"
		return result;
	}
}
