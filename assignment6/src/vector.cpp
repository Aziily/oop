#include "vector.hpp"
template class Vector<int> ;
template class Vector<double> ;
template class Vector<string> ;

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
    if (index < 0 || index >= m_nSize) {
        throw out_of_range("Index out of range");
    }
    return m_pElements[index];
}

template <class T>
inline T& Vector<T>::at(int index) {
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
    if (m_nSize == m_nCapacity) {
        inflate();
    }
    m_pElements[m_nSize] = x;
    m_nSize++;
}

template <class T>
inline T& Vector<T>::pop_back() {
    if (m_nSize == 0) {
        throw out_of_range("Vector is empty");
    }
    m_nSize--;
    return m_pElements[m_nSize];
}

template <class T>
inline void Vector<T>::resize(int n) {
    if (n > m_nCapacity) {
        m_nCapacity = n;
        T *temp = new T[m_nCapacity];
        for (int i = 0; i < m_nSize; i++) {
            temp[i] = m_pElements[i];
        }
        delete[] m_pElements;
        m_pElements = temp;
    } else {
        for (int i = n; i < m_nSize; i++) {
            m_pElements[i].~T();
        }
    }
    m_nSize = n;
}

template <class T>
inline void Vector<T>::deleteAt(int index) {
    if (index < 0 || index >= m_nSize) {
        throw out_of_range("Index out of range");
    }
    for (int i = index; i < m_nSize - 1; i++) {
        m_pElements[i] = m_pElements[i + 1];
    }
    m_pElements[m_nSize - 1].~T();
    m_nSize--;
}

template <class T>
inline void Vector<T>::clear() {
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
    m_nCapacity = m_nCapacity * 2 + 1;
    T *temp = new T[m_nCapacity];
    for (int i = 0; i < m_nSize; i++) {
        temp[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = temp;
}

template <class T>
inline void Vector<T>::print() const {
    cout << "Size: " << m_nSize << " - " ;
    cout << "[" ;
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