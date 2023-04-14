#include "pdremove.hpp"

int PDRemove::remove() {
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
    for (auto dairy = dairies.begin(); dairy != dairies.end(); dairy++) {
        if (dairy->year == year && dairy->month == month && dairy->day == day) {
            dairies.erase(dairy);
            cout << "Dairy removed." << endl;
            return 0;
        }
    }
    cout << "No dairy found." << endl;
    return -1;
}