// Workshop 8 - Smart Pointers
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include "DataBase.h"
#include "Profile.h"

namespace sdds
{
	// 
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
}

#endif
