// Workshop 8 - Smart Pointers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 16, 2023

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include "DataBase.h"
#include "Profile.h"

namespace sdds
{
	// Function compares the profiles in the two received DataBase objects. 
	// Two profiles are considered same if they have same age and name.
	// Returns a copy of Profile objects
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
}

#endif
