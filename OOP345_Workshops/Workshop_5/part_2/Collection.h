// Workshop 5 - Functions and Error Handling
// Name:	Sasawat Yimleang
// ID:		114036221
// E-mail:	syimleang@myseneca.ca
// Date:	2023/10/15

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <string>

namespace sdds
{
    template <typename T>
    class Collection
    {
        std::string m_name{};   // The name of the collection;
        T* m_item{ nullptr };   // A dynamically allocated array of items T
        size_t m_numOfCol{};    // The size of the array

        // A pointer to a function that returns void and receives two parameters of type const Collection<T>& and const T& in that order
        void (*m_observer) (const Collection<T>&, const T&) { nullptr };

    public:
        // Sets the name of the collection to the string referred to by the parameter and sets all other attributes to their default value
        Collection(const std::string& name) : m_name(name) {}

        // Rules of five
        ~Collection() {
            if (m_item)
                delete[] m_item;
        }
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;

        // A query that returns the name of the collection.
        const std::string& name() const {
            return m_name;
        }

        // A query that returns the number of items in the collection.
        size_t size() const {
            return m_numOfCol;
        }

        // stores the address of the callback function (observer) into an attribute. 
        // This parameter is a pointer to a function that returns void and accepts two parameters: 
        // a collection and an item that has just been added to the collection. 
        // This function is called when an item is added to the collection.
        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            m_observer = observer;
        }

        // Adds a copy of item to the collection, only if the collection doesn't contain an item with the same title. 
        // If item is already in the collection, this function does nothing
        Collection<T>& operator+=(const T& item) {
            bool sameTitle = false;

            // Checks if the title is same, then this function does nothing.
            for (auto i = 0u; i < m_numOfCol; ++i) {
                if (m_item[i].title() == item.title())
                    sameTitle = true;
            }

            // If title of received item does not same as current title.
            if (!sameTitle) {
                // Checks if ollection is empty, then assign the m_item to received item.
                if (m_numOfCol == 0u) {
                    m_item = new T[++m_numOfCol];
                    m_item[0] = item;
                }
                // If the colletion is exist 
                else {
                    // Create temporary item to holds the current item.
                    T* tempItem = new T[m_numOfCol];
                    for (auto i = 0u; i < m_numOfCol; ++i)
                        tempItem[i] = m_item[i];

                    // Resize current item
                    delete[] m_item;
                    m_item = nullptr;
                    m_item = new T[++m_numOfCol];

                    // Copy the temporary items to the current items
                    for (auto i = 0u; i < m_numOfCol - 1u; ++i)
                        m_item[i] = tempItem[i];

                    // Add the received item to the current items.
                    m_item[m_numOfCol - 1u] = item;

                    // Deallocate temporary items
                    delete[] tempItem;
                    tempItem = nullptr;

                    // If an observer has been registered, this operator calls the observer function 
                    // passing the current object (*this) and the new item as arguments
                    if (m_observer)
                        m_observer(*this, item);
                }
            }
            return *this;
        }

        // If the index is out of range throws an exception of type std::out_of_range with the message 
        // "Bad index [IDX]. Collection has [SIZE] items"
        T& operator[](size_t idx) const {
            if (idx >= size()) {
                std::string err = "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(size()) + "] items.";
                throw std::out_of_range(err);
            }
            return m_item[idx];
        }

        // returns the address of the item with the title title (type T has a member function called title() that returns the title of the item). 
        // If no such item exists, this function returns nullptr
        T* operator[](const std::string& title) const {
            // Loop to find the matching title
            for (auto i = 0u; i < m_numOfCol; ++i) {
                if (m_item[i].title() == title)
                    return &m_item[i];
            }

            // If there is no matched title, return nullptr
            return nullptr;
        }
    };

    // overload the insertion operator to insert the content of a Collection object into an ostream object. 
    // Iterate over all elements in the collection and insert each one into the ostream object
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& col) {
        for (auto i = 0u; i < col.size(); ++i)
            os << col[i];
        return os;
    }
}
#endif // !SDDS_COLLECTION_H