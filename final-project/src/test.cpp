#include "bin.hpp"
#include <map>
#include <list>
#include <set>
#include <vector>
#include <string>

using namespace std;

bool TestBin() {
    //test string
    cout << "test string" << endl;
    string str = "Hello World!", str2;
    Bin::Serialize(str, "str.txt");
    cout << "origin string: " << str << endl;
    Bin::Deserialize(str2, "str.txt");
    cout << "deserialzed string: " << str2 << endl;

    //test int
    cout << "test int" << endl;
    int num = 123456789, num2;
    Bin::Serialize(num, "num.txt");
    cout << "origin int: " << num << endl;
    Bin::Deserialize(num2, "num.txt");
    cout << "deserialzed int: " << num2 << endl;

    //test double
    cout << "test double" << endl;
    double d = 123456789.123456789, d2;
    Bin::Serialize(d, "d.txt");
    cout << "origin double: " << d << endl;
    Bin::Deserialize(d2, "d.txt");
    cout << "deserialzed double: " << d2 << endl;

    //test list
    cout << "test list" << endl;
    list<int> l = {1, 2, 3, 4, 5}, l2;
    Bin::Serialize(l, "l.txt");
    cout << "origin list: ";
    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    Bin::Deserialize(l2, "l.txt");
    cout << "deserialzed list: ";
    for (auto it = l2.begin(); it != l2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    //test set
    cout << "test set" << endl;
    set<int> s = {1, 2, 3, 4, 5}, s2;
    Bin::Serialize(s, "s.txt");
    cout << "origin set: ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    Bin::Deserialize(s2, "s.txt");
    cout << "deserialzed set: ";
    for (auto it = s2.begin(); it != s2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    //test vector
    cout << "test vector" << endl;
    vector<int> v = {1, 2, 3, 4, 5}, v2;
    Bin::Serialize(v, "v.txt");
    cout << "origin vector: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    Bin::Deserialize(v2, "v.txt");
    cout << "deserialzed vector: ";
    for (auto it = v2.begin(); it != v2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    //test map
    cout << "test map" << endl;
    map<int, int> m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, m2;
    Bin::Serialize(m, "m.txt");
    cout << "origin map: ";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;
    Bin::Deserialize(m2, "m.txt");
    cout << "deserialzed map: ";
    for (auto it = m2.begin(); it != m2.end(); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;

    //test pair
    cout << "test pair" << endl;
    pair<int, int> p = {1, 1}, p2;
    Bin::Serialize(p, "p.txt");
    cout << "origin pair: " << p.first << ":" << p.second << endl;
    Bin::Deserialize(p2, "p.txt");
    cout << "deserialzed pair: " << p2.first << ":" << p2.second << endl;

    //test composed data structure
    cout << "test map<int, list<int>>" << endl;
    map<int, list<int>> ml = {
        {1, {1, 2, 3, 4, 5}},
        {2, {6, 7, 8, 9, 10}},
        {3, {11, 12, 13, 14, 15}},
        {4, {16, 17, 18, 19, 20}},
        {5, {21, 22, 23, 24, 25}}
    }, ml2;
    Bin::Serialize(ml, "ml.txt");
    cout << "origin compised data structure: " << endl;
    for (auto it = ml.begin(); it != ml.end(); ++it) {
        cout << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    Bin::Deserialize(ml2, "ml.txt");
    cout << "deserialzed compised data structure: " << endl;
    for (auto it = ml2.begin(); it != ml2.end(); ++it) {
        cout << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }

    //test composed data structure
    cout << "test vector<list<int>>" << endl;
    vector<list<int>> vl = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    }, vl2;
    Bin::Serialize(vl, "vl.txt");
    cout << "origin compised data structure: " << endl;
    for (auto it = vl.begin(); it != vl.end(); ++it) {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    Bin::Deserialize(vl2, "vl.txt");
    cout << "deserialzed compised data structure: " << endl;
    for (auto it = vl2.begin(); it != vl2.end(); ++it) {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }

    //test composed data structure
    cout << "test set<list<int>>" << endl;
    set<list<int>> sl = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    }, sl2;
    Bin::Serialize(sl, "sl.txt");
    cout << "origin compised data structure: " << endl;
    for (auto it = sl.begin(); it != sl.end(); ++it) {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    Bin::Deserialize(sl2, "sl.txt");
    cout << "deserialzed compised data structure: " << endl;
    for (auto it = sl2.begin(); it != sl2.end(); ++it) {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
            cout << *it2 << " ";
        }
        cout << endl;
    }

    //test composed data structure
    cout << "test map<int, vector<list<char>, set<float>>>" << endl;      
    map<int, vector<pair<list<char>, set<float>>>> mvl, mvl2;
    for (int i = 0; i < 5; ++i) {
        vector<pair<list<char>, set<float>>> vpl;
        for (int j = 0; j < 5; ++j) {
            list<char> lc;
            for (int k = 0; k < 5; ++k) {
                lc.push_back('a' + k);
            }
            set<float> sf;
            for (int k = 0; k < 5; ++k) {
                sf.insert(1.1 * k);
            }
            vpl.push_back({lc, sf});
        }
        mvl.insert({i, vpl});
    }
    Bin::Serialize(mvl, "mvl.txt");
    cout << "origin compised data structure: " << endl;
    for (auto it = mvl.begin(); it != mvl.end(); ++it) {
        cout << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            cout << "{";
            for (auto it3 = it2->first.begin(); it3 != it2->first.end(); ++it3) {
                cout << *it3 << " ";
            }
            cout << "} {";
            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
                cout << *it3 << " ";
            }
            cout << "} ";
        }
        cout << endl;
    }
    Bin::Deserialize(mvl2, "mvl.txt");
    cout << "deserialzed compised data structure: " << endl;
    for (auto it = mvl2.begin(); it != mvl2.end(); ++it) {
        cout << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            cout << "{";
            for (auto it3 = it2->first.begin(); it3 != it2->first.end(); ++it3) {
                cout << *it3 << " ";
            }
            cout << "} {";
            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
                cout << *it3 << " ";
            }
            cout << "} ";
        }
        cout << endl;
    }

}