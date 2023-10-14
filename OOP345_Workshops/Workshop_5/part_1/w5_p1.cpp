// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/14

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h"
#include <string>	// Cannot use
#include "Book.h" // intentional

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	sdds::Book library[7];
	if (argc == 2) {
		// load the collection of books from the file "argv[1]".
		std::ifstream file(argv[1]);

		// Check if open the file properly.
		if (file) {
			std::string line;
			int bookIndex = 0;

			// Read one line at a time, and pass it to the Book constructor
			while (std::getline(file, line)) {

				// Lines that start with "#" are considered comments and be ignored
				if (line[0] == '#')
					continue;

				// Store each book read into the array "library"
				library[bookIndex] = sdds::Book(line);
				bookIndex++;

				// Break if we have read all available books
				if (bookIndex >= 7)
					break;
			}

			// Close the file
			file.close();
		}

		// if the file cannot be open, print a message to standard error console and
		// exit from application with error code "AppErrors::CannotOpenFile"
		else {
			std::cerr << "ERROR: Cannot open the file '" << argv[1] << "'." << std::endl;
			return AppErrors::CannotOpenFile;
			
		}
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// A lambda expression that fixes the price of a book accoding to the rules
	// The expression receive a single parameter of type "Book&"

	auto updateBookPrice = [&](sdds::Book& book) {
		// If the book was published in US, multiply the price with "usdToCadRate" and save the new price in the book object.
		if (book.country() == "US")
			book.price() *= usdToCadRate;

		// If the book was published in UK between 1990 and 1999 (inclussive), multiply the price with "gbpToCadRate" and save the new price in the book object.
		else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999)
			book.price() *= gbpToCadRate;
		};


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
	for (const sdds::Book& book : library)
		std::cout << book << std::endl;


	std::cout << "-----------------------------------------\n\n";

	// TODO: iterate over the library and update the price of each book
	//         using the lambda defined above.
	for (sdds::Book& book : library)
		updateBookPrice(book);


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	// TODO: iterate over the library and print each book to the screen
	for (const sdds::Book& book : library)
		std::cout << book << std::endl;


	std::cout << "-----------------------------------------\n";

	return cout;
}
