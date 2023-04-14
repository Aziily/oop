#include "base.hpp"

Base::Base(string file_path) {
    this->file_path = file_path; // store the file path
    load(); // load the data from the file
}

Base::~Base() {
    save(); // save the data to the file
}

void Base::load() {
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Error: file not found" << endl;
        return;
    }
    // read the data from the file
    string line;
    while (getline(file, line)) {
        // read the data from the file
        int year, month, day;
        string title, category, description;
        vector<string> content;
        stringstream ss(line);
        ss >> year >> month >> day;
        getline(file, title);
        getline(file, description);
        getline(file, category);
        // read the content
        string temp;
        getline(file, temp);
        while (temp!="^&*") {
            content.push_back(temp);
            getline(file, temp);
        }
        dairies.emplace(Dairy(year, month, day, title, content, category, description));
    }
    file.close();
}

void Base::save() {
    ofstream file(file_path);
    if (!file.is_open()) {
        cout << "Error: file not found" << endl;
        return;
    }
    // write the data to the file
    for (auto dairy : dairies) {
        file << dairy.year << " " << dairy.month << " " << dairy.day << endl;
        file << dairy.title << endl;
        file << dairy.description << endl;
        file << dairy.category << endl;
        for (auto line : dairy.content) {
            file << line << endl;
        }
        file << "^&*" << endl;
    }
    file.close();
}

bool Base::less_than(Dairy dairy1, Dairy dairy2) {
    return dairy1 < dairy2;
}