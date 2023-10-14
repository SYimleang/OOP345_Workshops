// Workshop 3 - Templates
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/01

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace sdds {
    template <typename T, unsigned C>
    class Collection {
        T m_items[C];
        unsigned m_cnt{};

        static T m_smallestItem;
        static T m_largestItem;

    protected:
        // The method assign the smallest item to m_smallestItem variable.
        void setSmallestItem(const T& newSmallest) {
            if (newSmallest < m_smallestItem)
                m_smallestItem = newSmallest;
        }

        // The method assign the largest item to m_largestItem variable.
        void setLargestItem(const T& newLargest) {
            if (newLargest > m_largestItem)
                m_largestItem = newLargest;
        }

    public:


        // A query to return current number of items
        unsigned size() const { return m_cnt; }

        // A query to return capacity of the collection
        unsigned capacity() const { return C; }

        // A mutator to receive as parameter an unmodifiable reference to object of type T. 
        bool operator+=(const T& newItem) {
            bool added{};

            // If the collection doesn't have room for more items (the size is the same as capacity), 
            // this function does nothing and returns false
            if ((added = m_cnt < C))
            {
                // Updates the smallest/largest to the value of parameter by calling the respective private member functions
                if (newItem < m_smallestItem) {
                    // Set the output to 1 decimal point.
                    std::cout.setf(std::ios::fixed);
                    std::cout.precision(1);
                    setSmallestItem(newItem);
                }
                else if (newItem > m_largestItem)
                    setLargestItem(newItem);

                // Adds the received object as a new item to the end of the collection of the collection.
                m_items[m_cnt++] = newItem;
            }
            return added;
        }

        // Returns the current smallest item stored in the class attribute.
        static T getSmallestItem() {
			return m_smallestItem;
        }

        // Returns the current largest item stored in the class attribute.
        static T getLargestItem(){ return m_largestItem; }

        // A query to receive a reference to an ostream object, and to insert into it all items existing in the collection; 
        // take a hint from sample output for formatting the output data.
        std::ostream& print(std::ostream& os) const {
            std::cout << '[';

            // Prints the item and a comma for all but last item
            for (size_t i = 0; i < m_cnt - 1; i++)
                std::cout << m_items[i] << ',';

            // Prints last item without comma after
            return std::cout << m_items[m_cnt - 1] << "]\n";
        }
    };

    // Initialize m_smallestItem.
    template<typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = 9999;

    // Initialize m_largestItem.
    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = -9999;

    // Specialize the definition of m_smallestItem object.
    template <>
    Book Collection<Book, 10> :: m_smallestItem("", 1, 10000);

    // Specialize the definition of m_largestItem object.
    template <>
    Book Collection<Book, 10> ::m_largestItem("", 10000, 1);
}
#endif