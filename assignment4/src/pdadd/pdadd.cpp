#include "pdadd.hpp"

void PDAdd::add() {
    // Get user input.
    int year, month, day;
    string title, description, category;
    vector<string> content;
    cout << "Year: ";
    cin >> year;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    cout << "Title: ";
    cin >> title;
    cin.get();
    cout << "Description: " << endl;
    getline(cin, description);
    cout << "Category: " << endl;
    getline(cin, category);
    cout << "Content: " << endl;
    string temp;
    while (temp != "." && temp[0] != EOF) {
        cin >> temp;
        content.push_back(temp);
    }

    // Judge if the dairy already exists.
    Dairy newDairy = Dairy(year, month, day, title, content, category, description);
    for (auto dairy = dairies.begin(); dairy != dairies.end(); dairy++) {
        // If the dairy already exists, remove it.
        if (newDairy == *dairy) {
            dairies.erase(dairy);
        }
    }
    // Add the dairy.
    dairies.emplace(Dairy(year, month, day, title, content, category, description));
}