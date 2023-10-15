// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"

using namespace std;

namespace sdds
{
    // Constructor initialize SpellChecker object (m_goodWords, m_badWords)
    SpellChecker::SpellChecker(const char* filename) {
        ifstream file(filename);

        // If the file is missing, this constructor throws an exception of type const char*, with the message Bad file name!
        if (!file) {
            throw "Bad file name!";
        }

        // If the file exists, this constructor loads its contents.
        else {
            string line = "";
            size_t cnt = 0u;
            int space = 0;

            // Lopping to read the content until reaches 6 words or there are no words.
            while (cnt < 6 && getline(file, line)) {

                // Removes the space from the beginning and end of bad words
                line.erase(0, line.find_first_not_of(' '));
                space = line.find(' ');
                m_badWords[cnt] = line.substr(0, space);

                // Delete the first word until space
                line.erase(0, space);

                // Removes the space from the beginning and end of good words
                line.erase(0, line.find_first_not_of(' '));
                space = line.find(' ');
                m_goodWords[cnt] = line.substr(0, space);

                ++cnt;
            }
        }
    }

    // Overload operator "()"
    void SpellChecker::operator()(std::string& text) {
        // Loop all the words.
        for (auto i = 0; i < 6; ++i) {
            // Loop to find any misspelled word.
            while (text.find(m_badWords[i]) != string::npos) {
                // Replace the bad word to the good word
                text.replace(text.find(m_badWords[i]), m_badWords[i].size(), m_goodWords[i]);
                ++m_replaceCount[i];
            }
        }
    }

    // Insert the all replaccement content to ostream
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics" << endl;
        // Loop to insert the replacement content to ostream
        for (auto i = 0u; i < 6; ++i)
            out << setw(15) << std::right << m_badWords[i] << ": " << m_replaceCount[i] << " replacements" << std::left << endl;
    }
}