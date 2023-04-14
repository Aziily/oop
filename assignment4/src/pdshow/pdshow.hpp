#ifndef _PDSHOW_HPP_
#define _PDSHOW_HPP_

#include "base.hpp"

/// @brief PDShow class
class PDShow : public Base {
public:
    /// @brief PDShow constructor
    /// @param file_path path of the file
    PDShow(string file_path) : Base(file_path) {}
    /// @brief show dairies
    void show();
    /// @brief PDShow destructor
    ~PDShow() {}
};

#endif