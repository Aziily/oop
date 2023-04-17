#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <stdexcept>

using namespace std;

/// @brief Vector class
/// @tparam T type of elements
template <class T>
class Vector {
public:
    /// @brief default constructor
    Vector();
    /// @brief constructor with size
    /// @param size size of vector
    Vector(int size);
    /// @brief copy constructor
    /// @param r Vector to copy
    Vector(const Vector &r);
    /// @brief destructor
    ~Vector();

public:
    /// @brief redefine operator[]
    /// @param index index of element
    /// @return reference to element
    T& operator[](int index);

public:
    /// @brief get element at index
    /// @param index index of element
    /// @return reference to element
    T& at(int index);
    /// @brief get size of vector
    /// @return size of vector
    int size() const;
    /// @brief push element to back of vector
    /// @param x element to push
    void push_back(const T& x);
    /// @brief pop element from back of vector
    /// @return element popped
    T& pop_back();
    /// @brief resize vector
    /// @param n new size of vector
    void resize(int n);
    /// @brief insert element at index
    /// @param index index to insert
    void deleteAt(int index);
    /// @brief clear vector
    void clear();
    /// @brief check if vector is empty
    /// @return true if vector is empty, false otherwise
    bool empty() const;

    /// @brief print vector to help debug and test
    void print() const;

private:
    /// @brief inflate vector with 2*capacity+1
    void inflate();

    T *m_pElements;     // pointer to elements
    int m_nSize;        // size of vector
    int m_nCapacity;    // capacity of vector
};

template <class T>
inline Vector<T>::Vector() {
    m_nSize = 0;
    m_nCapacity = 0;
    m_pElements = nullptr;
}

template <class T>
inline Vector<T>::Vector(int size) {
    m_nSize = 0;
    m_nCapacity = size;
    m_pElements = new T[size];
}

template <class T>
inline Vector<T>::Vector(const Vector &r) {
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    m_pElements = new T[m_nCapacity];
    // copy elements
    for (int i = 0; i < m_nSize; i++) {
        m_pElements[i] = r.m_pElements[i];
    }
}

template <class T>
inline Vector<T>::~Vector() {
    delete[] m_pElements;
}

template <class T>
inline T& Vector<T>::operator[](int index) {
    // check index
    if (index < 0 || index >= m_nSize) {
        throw out_of_range("Index out of range");
    }
    return m_pElements[index];
}

template <class T>
inline T& Vector<T>::at(int index) {
    // check index
    if (index < 0 || index >= m_nSize) {
        throw out_of_range("Index out of range");
    }
    return m_pElements[index];
}

template <class T>
inline int Vector<T>::size() const {
    return m_nSize;
}

template <class T>
inline void Vector<T>::push_back(const T& x) {
    // if vector is full, inflate it
    if (m_nSize == m_nCapacity) {
        inflate();
    }
    m_pElements[m_nSize] = x;
    m_nSize++;
}

template <class T>
inline T& Vector<T>::pop_back() {
    // check if vector is empty
    if (m_nSize == 0) {
        throw out_of_range("Vector is empty");
    }
    m_nSize--;
    return m_pElements[m_nSize];
}

template <class T>
inline void Vector<T>::resize(int n) {
    // check if n is valid
    if (n > m_nCapacity) { // inflate
        m_nCapacity = n;
        T *temp = new T[m_nCapacity];
        for (int i = 0; i < m_nSize; i++) {
            temp[i] = m_pElements[i];
        }
        delete[] m_pElements;
        m_pElements = temp;
    } else { // delete elements
        for (int i = n; i < m_nSize; i++) {
            m_pElements[i].~T();
        }
    }
    m_nSize = n;
}

template <class T>
inline void Vector<T>::deleteAt(int index) {
    // check index
    if (index < 0 || index >= m_nSize) {
        throw out_of_range("Index out of range");
    }
    // delete element at index
    for (int i = index; i < m_nSize - 1; i++) {
        m_pElements[i] = m_pElements[i + 1];
    }
    m_pElements[m_nSize - 1].~T();
    m_nSize--;
}

template <class T>
inline void Vector<T>::clear() {
    // delete all elements
    if (m_nSize > 0) {
        for (int i = 0; i < m_nSize; i++) {
            m_pElements[i].~T();
        }
    }
    m_nSize = 0;
}

template <class T>
inline bool Vector<T>::empty() const {
    return m_nSize == 0;
}

template <class T>
inline void Vector<T>::inflate() {
    // inflate vector with 2*capacity+1
    m_nCapacity = m_nCapacity * 2 + 1;
    T *temp = new T[m_nCapacity];
    // copy elements
    for (int i = 0; i < m_nSize; i++) {
        temp[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = temp;
}

template <class T>
inline void Vector<T>::print() const {
    // print vector to help debug and test
    cout << "Capacity: " << m_nCapacity << endl;
    cout << "Size: " << m_nSize << endl;
    cout << "Elements: [";
    // special start
    if (m_nSize > 0) {
        cout << m_pElements[0];
    }
    if (m_nSize > 1) {
        for (int i = 1; i < m_nSize; i++) {
            cout << ", " << m_pElements[i];
        }
    }
    cout << "]" << endl;
}

#endif