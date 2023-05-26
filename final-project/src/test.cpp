#include "bin.hpp"
#include <map>
#include <list>
#include <set>
#include <vector>
#include <string>

using namespace std;

bool TestBin() {
    //test string
    string str = "Hello World!", str2;
    Bin::SerializeBin(str, "str.txt");
    Bin::DeserializeBin(str2, "str.txt");
    cout << "origin string: " << str << endl;
    cout << "deserialzed string: " << str2 << endl;

    //test int
    int num = 123456789, num2;
    Bin::SerializeBin(num, "num.txt");
    Bin::DeserializeBin(num2, "num.txt");
    cout << "origin int: " << num << endl;
    cout << "deserialzed int: " << num2 << endl;

    //test double
    double d = 123456789.123456789, d2;
    Bin::SerializeBin(d, "d.txt");
    Bin::DeserializeBin(d2, "d.txt");
    cout << "origin double: " << d << endl;
    cout << "deserialzed double: " << d2 << endl;

    //test map
    map<string, int> m, m2;
    m["Hello"] = 1;
    m["World"] = 2;
    Bin::SerializeBin(m, "m.txt");
    Bin::DeserializeBin(m2, "m.txt"); 
    cout << "origin map: " << endl;
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
    cout << "deserialzed map: " << endl;
    for (auto it = m2.begin(); it != m2.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    //test list
    list<int> l, l2;
    vector<int> v;
    set<int> s;
}