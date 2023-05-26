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

    //test vector
    vector<int> v, v2;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    Bin::SerializeBin(v, "v.txt");
    Bin::DeserializeBin(v2, "v.txt");
    cout << "origin vector: " << endl;
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "deserialzed vector: " << endl;
    for (auto it = v2.begin(); it != v2.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    //test set
    set<int> s, s2;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    Bin::SerializeBin(s, "s.txt");
    Bin::DeserializeBin(s2, "s.txt");
    cout << "origin set: " << endl;
    for (auto it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "deserialzed set: " << endl;
    for (auto it = s2.begin(); it != s2.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

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
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    Bin::SerializeBin(l, "l.txt");
    Bin::DeserializeBin(l2, "l.txt");
    cout << "origin list: " << endl;
    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "deserialzed list: " << endl;
    for (auto it = l2.begin(); it != l2.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    
    //test pair
    pair<int, string> p, p2;
    p.first = 1;
    p.second = "Hello";
    Bin::SerializeBin(p, "p.txt");
    Bin::DeserializeBin(p2, "p.txt");
    cout << "origin pair: " << endl;
    cout << p.first << " " << p.second << endl;
    cout << "deserialzed pair: " << endl;
    cout << p2.first << " " << p2.second << endl;
}