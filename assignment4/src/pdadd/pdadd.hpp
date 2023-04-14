#ifndef _PDADD_HPP_
#define _PDADD_HPP_

#include "base.hpp"

/// @brief PDAdd class
class PDAdd : public Base {
public:
    /// @brief PDAdd constructor
    /// @param file_path path of the file
    PDAdd(string file_path) : Base(file_path) {}
    /// @brief add dairies
    void add();
    /// @brief PDAdd destructor
    ~PDAdd() {}
};

#endif