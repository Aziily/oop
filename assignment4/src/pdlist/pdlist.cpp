#include "pdlist.hpp"

void PDList::list() {
    // Change the format to sort.
    vector<Dairy> dairiesVec = vector<Dairy>(dairies.begin(), dairies.end());
    sort(dairiesVec.begin(), dairiesVec.end());
    int start_year = -1, start_month = -1, start_day = -1;
    int end_year = -1, end_month = -1, end_day = -1;

    // Get date range.
    string line;
    cin.get();
    cout << "Start date (yyyy mm dd):(no input for no limit) " << endl;
    getline(cin, line);
    if (line != "") {
        stringstream ss(line);
        ss >> start_year >> start_month >> start_day;
    }
    cout << "End date (yyyy mm dd):(no input for no limit) " << endl;
    getline(cin, line);
    if (line != "") {
        stringstream ss(line);
        ss >> end_year >> end_month >> end_day;
    }
    cout << endl;

    // Print dairies.
    cout << "Dairies:" << endl;
    for (auto dairy : dairiesVec) {
        // Check date range.
        if (start_year != -1 && dairy <= Dairy(start_year, start_month, start_day, "", {})) continue;
        if (end_year != -1 && dairy >= Dairy(end_year, end_month, end_day, "", {})) continue;
        cout << dairy.year << "-" << dairy.month << "-" << dairy.day << "-" << dairy.title << endl;
    }
}