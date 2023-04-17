#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class Vector {
public:
    Vector();
    Vector(int size);
    Vector(const Vector &r);
    ~Vector();
    T& operator[](int index);
    T& at(int index);
    int size() const;
    void push_back(const T& x);
    T& pop_back();
    void resize(int n);
    void deleteAt(int index);
    void clear();
    bool empty() const;

    void print() const;

private:
    void inflate();
    T *m_pElements;
    int m_nSize;
    int m_nCapacity;
};

#endif