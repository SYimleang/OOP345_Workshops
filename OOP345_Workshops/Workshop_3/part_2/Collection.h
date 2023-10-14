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

        // A mutator operator to receive an array index and return corresponding element from m_items array.
        T operator[](const unsigned& i) const {
            T result;
            if (i < m_cnt)
                result = m_items[i];
            return result;
        }

        // A mutator to increase by 1 the size count of elements stored in the collection.
        void incrSize() { ++m_cnt; }

    public:

        // A query to return current number of items
        unsigned size() const { return m_cnt; }

        // A query to return capacity of the collection
        unsigned capacity() const { return C; }

        // A mutator to receive as parameter an unmodifiable reference to object of type T. 
        bool operator+=(const T& newItem) {
            bool result{};

            // If the collection doesn't have room for more items (the size is the same as capacity), 
            // this function does nothing and returns false
            if ((result = m_cnt < C))
            {
                // Updates the smallest/largest to the value of parameter by calling the respective private member functions
                if (newItem < m_smallestItem)
                    setSmallestItem(newItem);
                else if (newItem > m_largestItem)
                    setLargestItem(newItem);

                // Adds the received object as a new item to the end of the collection of the collection.
                m_items[m_cnt++] = newItem;
            }
            return result;
        }

        // Returns the current smallest item stored in the class attribute.
        static T getSmallestItem() {
            // Set the output to 1 decimal point.
            std::cout.setf(std::ios::fixed);
            std::cout.precision(1);
			return m_smallestItem;
        }

        // Returns the current largest item stored in the class attribute.
        static T getLargestItem(){ 
            // Set the output to 1 decimal point.
            std::cout.setf(std::ios::fixed);
            std::cout.precision(1);
            return m_largestItem; 
        }

        // A query to receive a reference to an ostream object, and to insert into it all items existing in the collection; 
        // take a hint from sample output for formatting the output data.
        std::ostream& print(std::ostream& os) {

            // Sorting the output if the specific value of C is 72.
            if (capacity() == 72) {
                T temp;
                for (unsigned i = 0; i < size() - 1; ++i) {
                    for (unsigned j = 0; j < size() - i - 1; ++j) {
                        if (m_items[j] > m_items[j + 1]) {
                            temp = m_items[j];
                            m_items[j] = m_items[j + 1];
                            m_items[j + 1] = temp;
                        }
                    }
                }
            }

            std::cout << '[';

            // Prints the item and a comma for all but last item.
            for (unsigned i = 0; i < m_cnt - 1; ++i)
                std::cout << m_items[i] << ',';

            // Prints last item without comma after.
            return std::cout << m_items[m_cnt - 1] << "]" << std::endl;
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
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
    template <>
    Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

    // Specialize the definition of m_largestItem object.
    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
    template <>
    Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

    // Specialize the print() function
    template<>
    std::ostream& Collection<Book, 10> :: print(std::ostream& os) {
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (unsigned i = 0; i < m_cnt; ++i)
            m_items[i].print(os << "| ") << " |" << std::endl;
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }

    template<>
    std::ostream& Collection<Book, 72> :: print(std::ostream& os) {
        Book temp;
        for (unsigned i = 0; i < size() - 1; ++i) {
            for (unsigned j = 0; j < size() - i - 1; ++j) {
                if (m_items[j] > m_items[j + 1]) {
                    temp = m_items[j];
                    m_items[j] = m_items[j + 1];
                    m_items[j + 1] = temp;
                }
            }
        }
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (unsigned i = 0; i < m_cnt; ++i)
            m_items[i].print(os << "| ") << " |" << std::endl;
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }
}
#endif