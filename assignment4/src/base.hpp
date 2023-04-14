#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/// @brief Dairy struct
struct Dairy
{
    int year, month, day;   // date
    string title;           // title
    string description;     // description of the dairy (optional)
    string category;        // category of the dairy (optional)
    vector<string> content; // content of the dairy

    /// @brief Dairy constructor
    /// @param year year of the dairy
    /// @param month month of the dairy
    /// @param day day of the dairy
    /// @param title title of the dairy
    /// @param content content of the dairy
    /// @param category category of the dairy
    /// @param description description of the dairy
    Dairy(int year, int month, int day, string title, vector<string> content, string category="", string description="")
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->title = title;
        this->description = description;
        this->category = category;
        this->content = content;
    }
    /// Some operators for Dairy
    bool operator==(const Dairy& rhs) const
    {
        return year == rhs.year && month == rhs.month && day == rhs.day;
    }
    bool operator<(const Dairy& rhs) const
    {
        if (year < rhs.year) return true;
        if (year > rhs.year) return false;
        if (month < rhs.month) return true;
        if (month > rhs.month) return false;
        if (day < rhs.day) return true;
        return false;
    }
    bool operator>(const Dairy& rhs) const
    {
        if (year > rhs.year) return true;
        if (year < rhs.year) return false;
        if (month > rhs.month) return true;
        if (month < rhs.month) return false;
        if (day > rhs.day) return true;
        return false;
    }
    bool operator<=(const Dairy& rhs) const
    {
        return *this < rhs || *this == rhs;
    }
    bool operator>=(const Dairy& rhs) const
    {
        return *this > rhs || *this == rhs;
    }
    bool operator-(const Dairy& rhs) const
    {
        return *this < rhs || *this > rhs;
    }
};


class Base {
protected:
    string file_path;   // path of the file
    set<Dairy> dairies; // dairies
    /// @brief load dairies from file
    void load();
    /// @brief save dairies to file
    void save();

    /// @brief compare two dairies
    /// @param dairy1 dairy1
    /// @param dairy2 dairy2
    /// @return true if dairy1 < dairy2
    bool less_than(Dairy dairy1, Dairy dairy2);

public:
    /// @brief Base constructor
    /// @param file_path path of the file
    Base(string file_path);
    /// @brief Base destructor
    virtual ~Base();
};

#endif