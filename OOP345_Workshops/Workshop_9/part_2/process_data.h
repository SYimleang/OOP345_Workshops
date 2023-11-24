// Workshop 9 - Multi-Threading, Thread Class
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 24, 2023

#ifndef SDDS_PROCESSDATA_H
#define SDDS_PROCESSDATA_H

#include<string>

namespace sdds {
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg);
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var);

	// Class ProcessData
	class ProcessData {
		int total_items{};				// An integer number of total data items
		int* data{};					// The set of data
		int num_threads{ 0 };			// to hold number of threads 
		double* averages{ nullptr };	// to hold average factors 
		double* variances{ nullptr };	// to hold variance factors
		int* p_indices{ nullptr };		// to hold partitioning indices
	public:
		// Constructor with two arguments. This constructor receives the input file name as a string and the number of threads.
		// Read the data from the file and display the contents in the file and threading information.
		ProcessData(const std::string& input_file, int n_threads);

		// Rules of three
		~ProcessData();										// Destructor
		ProcessData(const ProcessData&) = delete;			// Prevent copy constructor
		ProcessData& operator=(const ProcessData&) = delete;// Prevent copy assignment operator
		ProcessData(ProcessData&&) = delete;				// Prevent move constructor
		ProcessData& operator=(ProcessData&&) = delete;		// Prevent move assignment operator

		// Overload operator bool. Return true if the items still remaining and data is valid.
		operator bool() const;

		// Overload operator (). This operator Computes the average value and Computes variance value, then writes to "target_file" in binary mode.
		// Return 0 if the process is complete. Otherwise, throw an error.
		int operator()(const std::string& target_file, double& avg, double& var);
	};
}

#endif
