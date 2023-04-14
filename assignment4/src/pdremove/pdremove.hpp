#ifndef _PDREMOVE_HPP_
#define _PDREMOVE_HPP_

#include "base.hpp"

/// @brief PDRemove class
class PDRemove : public Base {
public:
    /// @brief PDRemove constructor
    /// @param file_path path of the file
    PDRemove(string file_path) : Base(file_path) {}
    /// @brief remove dairies
    /// @return 0 if success, -1 if fail
    int remove();
    ~PDRemove() {}
};

#endif