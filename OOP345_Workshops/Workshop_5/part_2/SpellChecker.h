// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <iostream>

namespace sdds {
	class SpellChecker {
		std::string m_badWords[6];	// An array with 6 misspelled words
		std::string m_goodWords[6];	// An array with the correct spelling of those 6 words
		size_t m_replaceCount[6]{};	// 

	public:
		// Receives the address of a C-style null-terminated string that holds the name of the file that contains the misspelled words. 
		// If the file exists, this constructor loads its contents. If the file is missing, this constructor throws an exception of type const char*, with the message Bad file name!. 
		// Each line in the file has the format BAD_WORD  GOOD_WORD; 
		// the two fields can be separated by any number of spaces.
		SpellChecker(const char* filename);

		// This operator searches text and replaces any misspelled word with the correct version. 
		// It should also count how many times each misspelled word has been replaced.
		void operator()(std::string& text);

		// Inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance
		void showStatistics(std::ostream& out) const;
	};
}
#endif //!SDDS_SPELLCHECKER_H
