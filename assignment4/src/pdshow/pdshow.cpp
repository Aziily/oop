#include "pdshow.hpp"

void PDShow::show() {
    // Get date.
    int year, month, day;
    cout << "Year: ";
    cin >> year;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    cout << endl;

    // Find dairy.
    for (auto dairy : dairies) {
        if (dairy.year == year && dairy.month == month && dairy.day == day) {
            cout << dairy.title << endl;
            cout << "Time: " << dairy.year << "-" << dairy.month << "-" << dairy.day << endl;
            cout << "Description: " << dairy.description << endl;
            cout << "Category: " << dairy.category << endl;
            cout << "Content: " << endl;
            for (auto line : dairy.content) {
                cout << line << endl;
            }
            return;
        }
    }
    cout << "No dairy found." << endl;
}