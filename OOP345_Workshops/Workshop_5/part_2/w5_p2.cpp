// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     // intentional
#include "SpellChecker.h"
#include "SpellChecker.h"   // intentional
#include "Book.h"
#include "Book.h"           // intentional
#include "Movie.h"
#include "Movie.h"          // intentional

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
    #error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
    #error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
    #error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
	const sdds::Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection,
	const sdds::Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	sdds::Collection<sdds::Book> library("Bestsellers");
	if (argc == 5) {
		// Load the first 4 books from the file "argv[1]"
		std::ifstream readFile(argv[1]);

		// If the file cannot be open, print a message to standard error console and
		// exit from application with error code "AppErrors::CannotOpenFile"
		if (!readFile) {
			std::cout << "Cannot Open the File: " << argv[1] << std::endl;
			exit(AppErrors::CannotOpenFile);
		}

		std::string line{ "" };
		size_t cnt{ 0u };

		// read one line at a time, and pass it to the Book constructor
		while (cnt < 4 && std::getline(readFile, line)) {
			// Lines that start with "#" are considered comments and will be ignored
			if (line[0] != '#') {
				sdds::Book tempBook(line);
				// store each book read into the collection "library"
				library += tempBook;
				++cnt;
			}
		}

		/*
		 ♪ Hey, I just met you,      ♪
		 ♪ And this is crazy,        ♪
		 ♪ But here's my number.     ♪    (register the observer)
		 ♪ So, if something happens, ♪    (event)
		 ♪ Call me, maybe?           ♪    (callback)
		 */
		library.setObserver(bookAddedObserver);

		// Add the rest of the books from the file.
		while (std::getline(readFile, line)) {
			if (line[0] != '#') {
				sdds::Book tempBook(line);
				library += tempBook;
				++cnt;
			}
		}
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		std::exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	// A lambda expression that fixes the price of a book accoding to the rules.
	// receive a single parameter of type "Book&"
	auto exchagRate = [=](sdds::Book& book) {
		// If the book was published in US, multiply the price with "usdToCadRate" and save the new price in the book object.
		if (book.country() == "US")
			book.price() *= usdToCadRate;
		// If the book was published in UK between 1990 and 1999 (inclussive), multiply the price with "gbpToCadRate" and save the new price in the book object
		else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999)
			book.price() *= gbpToCadRate;

		return book;
		};


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	// Iterate over the library and update the price of each book by using the lambda function.
	for (auto i = 0u; i < library.size(); ++i)
		exchagRate(library[i]);

	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	sdds::Collection<sdds::Movie> theCollection("Action Movies");

	// Process the file
	sdds::Movie movies[5];
	if (argc > 2) {
		// Load 5 movies from the file "argv[2]"
		std::ifstream file(argv[2]);

		// If the file cannot be open, print a message to standard error console and
		// exit from application with error code "AppErrors::CannotOpenFile"
		if (!file) {
			std::cout << "Cannot Open the File: " << argv[2] << std::endl;
			exit(AppErrors::CannotOpenFile);
		}

		std::string line{ "" };
		size_t cnt{ 0 };

		// Read one line at a time, and pass it to the Movie constructor
		while (cnt < 5 && std::getline(file, line)) {
			// Lines that start with "#" are considered comments and will be ignored
			if (line[0] != '#' && cnt < 7) {
				// Store each movie read into the array "movies"
				sdds::Movie tempBook(line);
				movies[cnt++] = tempBook;
			}
		}
	}

	std::cout << "-----------------------------------------\n";
	std::cout << "Testing addition and callback function\n";
	std::cout << "-----------------------------------------\n";
	if (argc > 2) {
		// Add a few movies to collection; no observer is set
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		// add more movies; now we get a callback from the collection
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
	}
	else {
		std::cout << "** No movies in the Collection\n";
	}
	std::cout << "-----------------------------------------\n\n";
	
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing exceptions and operator[]\n";
	std::cout << "-----------------------------------------\n";

	try {
		for (auto i = 0u; i < 10; ++i)
			std::cout << theCollection[i];
	}
	// If an exception occurs print a message.
	catch (std::out_of_range& err) {
		std::cout << "** EXCEPTION: " << err.what() << std::endl;
	}
	catch (std::exception& err) {
		std::cout << "** EXCEPTION: " << err.what() << std::endl;
	}

	std::cout << "-----------------------------------------\n\n";


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing the functor\n";
	std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
		try {
			sdds::SpellChecker sp(argv[i]);
			for (auto j = 0u; j < library.size(); ++j)
				library[j].fixSpelling(sp);
			sp.showStatistics(std::cout);

			for (auto j = 0u; j < theCollection.size(); ++j)
				theCollection[j].fixSpelling(sp);
			sp.showStatistics(std::cout);
		}
		// If an exception occurs print a message.
		catch (const char* err) {
			std::cout << "** EXCEPTION: " << err << std::endl;
		}
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";

	std::cout << "=========================================\n";
	std::cout << "Wrapping up this workshop\n";
	std::cout << "--------------- Movies ------------------\n";
	std::cout << theCollection;
	std::cout << "--------------- Books -------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing operator[] (the other overload)\n";
	std::cout << "-----------------------------------------\n";
	const sdds::Movie* aMovie = theCollection["Terminator 2"];
	if (aMovie == nullptr)
		std::cout << "** Movie Terminator 2 not in collection.\n";
	aMovie = theCollection["Dark Phoenix"];
	if (aMovie != nullptr)
		std::cout << "In this collection:\n" << *aMovie;
	std::cout << "-----------------------------------------\n";

	return cout;
}
