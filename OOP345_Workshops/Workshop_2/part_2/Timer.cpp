// Workshop 2 - Move and Copy Semantics
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/09/24

#include <iostream>
#include "Timer.h"

namespace sdds {
    void Timer::start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    long long Timer::stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        return elapsed_time.count();
    }
}