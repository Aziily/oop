#ifndef _PDLIST_HPP_
#define _PDLIST_HPP_

#include "base.hpp"

/// @brief PDList class
class PDList : public Base {
public:
    /// @brief PDList constructor
    /// @param file_path path of the file
    PDList(string file_path) : Base(file_path) {}
    /// @brief list dairies
    void list();
    /// @brief PDList destructor
    ~PDList() {}
};

#endif