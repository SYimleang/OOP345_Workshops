// Workshop 9 - Multi-Threading, Thread Class
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	November 19, 2023

#ifndef SDDS_PROCESSDATA_H
#define SDDS_PROCESSDATA_H

#include<string>

namespace sdds {
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg);
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var);

	// Class ProcessData
	class ProcessData {
		int total_items{};	// An integer number of total data items
		int* data{};		// The set of data
	public:
		ProcessData(const std::string& input_file);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		int operator()(const std::string& target_file, double& avg, double& var);
	};
}

#endif
