// Workshop 3 - Templates
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/01

#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace sdds {
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:

        // Shadow the function operator+= to place or insert the received item into the array m_items 
        // at an appropriate index to ensure that the elements are in ascending order after insertion.
        bool operator+=(const T& newItem) {
            bool result{};
            Book temp;
            if ((result = this->size() < this->capacity())) {
                if (newItem < this->getSmallestItem())
                    this->setSmallestItem(newItem);
                else if (newItem > this->getLargestItem())
                    this->setLargestItem(newItem);

                // Adding by call operator+= of parent class (Need to define template argument list) 
                Collection<T, 72>::operator+=(newItem);
            }
            return result;
        }
    };
}
#endif // !SDDS_ORDEREDCOLLECTION_H