// Workshop 9 - Multi-Threading, Thread Class
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 19, 2023

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"

namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument.
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will
	//   hold average of the array elements. When they are different, avg will hold a value called
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of
	//   the array elements. When they are different, var will hold a value called as variance factor.
	//   For part 1, you will be using same value for size and double. Use of different values for size
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in
	//   binary mode for reading, reads first int data as total_items, allocate memory space
	//   to hold the data items, and reads the data items into the allocated memory space.
	//   It prints first five data items and the last three data items as data samples.
	//   
	ProcessData::ProcessData(const std::string& filename) {

		// Opens the file in binary mode (from received parameter)
		std::ifstream file(filename, std::ios::binary);

		// Check if the file is open properly
		if (!file) {
			std::cerr << "Error: Unable to open file " << filename << std::endl;
			return;
		}

		// Read the total number of data items (first 4 bytes)
		file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

		// Allocate memory for "data"
		data = new int[total_items];

		// Read the data items into the allocated memory ("data")
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

		// Display the contents of the file ("filename", "total_items" and "data"s)
		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;
	}

	// Destructor
	ProcessData::~ProcessData() {
		delete[] data;
	}

	// Overload operator bool. Return true if the items still remaining and data is valid.
	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr;
	}

	// Overload operator ()
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var)
	{
		// Compute the average value by calling computeAvgFactor
		computeAvgFactor(data, total_items, total_items, avg);
		// Compute variance value by calling computeVarFactor
		computeVarFactor(data, total_items, total_items, avg, var);

		// Opens the file in binary mode (Using "target_file")
		std::ofstream outFile(target_file, std::ios::binary);

		// Check the file can open properly
		if (!outFile) {
			// Display error message and throw an error
			std::cerr << "Error: Unable to open file " << target_file << " for writing" << std::endl;
			throw std::runtime_error("Unable to open the target file for writing.");
		}

		// Write "total_items" to the "target_file"
		outFile.write(reinterpret_cast<const char*>(&total_items), sizeof(int));

		// Write "data" to the "target_file"
		outFile.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

		return 0;
	}
}
