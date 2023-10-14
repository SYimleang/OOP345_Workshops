// Workshop 2 - Move and Copy Semantics
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/24

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {

	class Timer {
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

	public:
		void start();
		long long stop();
	};
}
#endif // SDDS_TIMER_H