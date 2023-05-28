#include "bin.hpp"
#include "xml.hpp"

using namespace std;

/// @brief the struct to test
struct test
{
    int idx;
    std::string name;
    std::vector<double> data;
};
// register the struct to binary serialization and deserialization
BEGIN_REGISTER_STRUCT_SERIALIZE_BIN(test)
    REGISTER_STRUCT_MEMBER_SERIALIZE_BIN(idx)
    REGISTER_STRUCT_MEMBER_SERIALIZE_BIN(name)
    REGISTER_STRUCT_MEMBER_SERIALIZE_BIN(data)
END_REGISTER_STRUCT_SERIALIZE_BIN()
BEGIN_REGISTER_STRUCT_DESERIALIZE_BIN(test)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_BIN(idx)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_BIN(name)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_BIN(data)
END_REGISTER_STRUCT_DESERIALIZE_BIN()

// register the struct to xml serialization and deserialization
BEGIN_REGISTER_STRUCT_SERIALIZE_XML(test)
    REGISTER_STRUCT_MEMBER_SERIALIZE_XML(idx)
    REGISTER_STRUCT_MEMBER_SERIALIZE_XML(name)
    REGISTER_STRUCT_MEMBER_SERIALIZE_XML(data)
END_REGISTER_STRUCT_SERIALIZE_XML()
BEGIN_REGISTER_STRUCT_DESERIALIZE_XML(test)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_XML(idx)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_XML(name)
    REGISTER_STRUCT_MEMBER_DESERIALIZE_XML(data)
END_REGISTER_STRUCT_DESERIALIZE_XML()


#define HEAD(name)  changeColor(CYAN);\
                    cout << "================================================================================" << endl;\
                    cout << "Begin test of " << name << " serialization and deserialization" << endl;\
                    cout << "================================================================================" << endl;\
                    int pass = 0, fail = 0, total = 0;
#define BEGIN(name) changeColor(YELLOW);\
                    cout << "[begin] test " << name << endl;
#define PASS(name)  changeColor(GREEN);\
                    cout << "[pass] test " << name << endl;\
                    pass++;\
                    total++;
#define FAIL(name)  changeColor(RED);\
                    cout << "[fail] test " << name << endl;\
                    fail++;\
                    total++;
#define ERROR   catch(const std::exception& e)\
                {\
                    changeColor(RED);\
                    std::cerr << "[fail] " << e.what() << '\n';\
                    fail++;\
                    total++;\
                }

/// @brief the namespace contains some test functions
namespace tester {
    static const string PRE = "../output/";     // the prefix of output file

    static const string WHITE = "\033[0m";      // white color
    static const string RED = "\033[31m";       // red color
    static const string GREEN = "\033[32m";     // green color
    static const string CYAN = "\033[36m";      // cyan color
    static const string YELLOW = "\033[33m";    // yellow color
    static const string PURPLE = "\033[35m";    // purple color

    /// @brief change the color of output
    /// @param color the color to change
    void changeColor(string color) {
        cout << color;
    }

    /// @brief test binary serialization and deserialization with different types
    /// @return true if all tests pass, false if any test fails
    bool TestBin() {
        HEAD("binary");

        // test bool
        BEGIN("bool");
        bool b = true, b2;
        try
        {
            bin::Serialize(b, PRE + "b.bin");
            bin::Deserialize(b2, PRE + "b.bin");
            if (b == b2) {
                PASS("bool");
            } else {
                FAIL("bool");
            }
        }
        ERROR;

        // test char
        BEGIN("char");
        char c = 'a', c2;
        try
        {
            bin::Serialize(c, PRE + "c.bin");
            bin::Deserialize(c2, PRE + "c.bin");
            if (c == c2) {
                PASS("char");
            } else {
                FAIL("char");
            }
        }
        ERROR;

        // test int
        BEGIN("int");
        int num = 123456789, num2;
        try
        {
            bin::Serialize(num, PRE + "num.bin");
            bin::Deserialize(num2, PRE + "num.bin");
            if (num == num2) {
                PASS("int");
            } else {
                FAIL("int");
            }
        }
        ERROR;

        // test float
        BEGIN("float");
        float f = 188.888888, f2;
        try
        {
            bin::Serialize(f, PRE + "f.bin");
            bin::Deserialize(f2, PRE + "f.bin");
            if (f == f2) {
                PASS("float");
            } else {
                FAIL("float");
            }
        }
        ERROR;
        

        // test double
        BEGIN("double");
        double d = 123456789.123456789, d2;
        try
        {
            bin::Serialize(d, PRE + "d.bin");
            bin::Deserialize(d2, PRE + "d.bin");
            if (d == d2) {
                PASS("double");
            } else {
                FAIL("double");
            }
        }
        ERROR;

        
        // test string
        BEGIN("string");
        string str = "Hello World!", str2;
        try
        {
            bin::Serialize(str, PRE + "str.bin");
            bin::Deserialize(str2, PRE + "str.bin");
            if (str == str2) {
                PASS("string");
            } else {
                FAIL("string");
            }
        }
        ERROR;

        // test list
        BEGIN("list");
        list<int> l = {1, 2, 3, 4, 5}, l2;
        try
        {
            bin::Serialize(l, PRE + "l.bin");
            bin::Deserialize(l2, PRE + "l.bin");
            bool flag = true;
            for (auto it1 = l.begin(), it2 = l2.begin(); it1 != l.end() && it2 != l2.end(); ++it1, ++it2) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("list");
            } else {
                FAIL("list");
            }
        }
        ERROR;

        // test set
        BEGIN("set");
        set<int> s = {1, 2, 3, 4, 5}, s2;
        try
        {
            bin::Serialize(s, PRE + "s.bin");
            bin::Deserialize(s2, PRE + "s.bin");
            bool flag = true;
            for (auto it1 = s.begin(), it2 = s2.begin(); it1 != s.end() && it2 != s2.end(); ++it1, ++it2) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("set");
            } else {
                FAIL("set");
            }
        }
        ERROR;

        // test vector
        BEGIN("vector");
        vector<int> v = {1, 2, 3, 4, 5}, v2;
        try
        {
            bin::Serialize(v, PRE + "v.bin");
            bin::Deserialize(v2, PRE + "v.bin");
            bool flag = true;
            for (auto it1 = v.begin(), it2 = v2.begin(); it1 != v.end() && it2 != v2.end(); ++it1, ++it2) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("vector");
            } else {
                FAIL("vector");
            }
        }
        ERROR;

        // test map
        BEGIN("map");
        map<int, int> m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, m2;
        try
        {
            bin::Serialize(m, PRE + "m.bin");
            bin::Deserialize(m2, PRE + "m.bin");
            bool flag = true;
            for (auto it1 = m.begin(), it2 = m2.begin(); it1 != m.end() && it2 != m2.end(); ++it1, ++it2) {
                if (it1->first != it2->first || it1->second != it2->second) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("map");
            } else {
                FAIL("map");
            }
        }
        ERROR;

        // test pair
        BEGIN("pair");
        pair<int, int> p = {1, 1}, p2;
        try
        {
            bin::Serialize(p, PRE + "p.bin");
            bin::Deserialize(p2, PRE + "p.bin");
            if (p.first == p2.first && p.second == p2.second) {
                PASS("pair");
            } else {
                FAIL("pair");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("map<int, list<int>>");
        map<int, list<int>> ml = {
            {1, {1, 2, 3, 4, 5}},
            {2, {6, 7, 8, 9, 10}},
            {3, {11, 12, 13, 14, 15}},
            {4, {16, 17, 18, 19, 20}},
            {5, {21, 22, 23, 24, 25}}
        }, ml2;
        try
        {
            bin::Serialize(ml, PRE + "ml.bin");
            bin::Deserialize(ml2, PRE + "ml.bin");
            bool flag = true;
            for (auto it1 = ml.begin(), it2 = ml2.begin(); it1 != ml.end() && it2 != ml2.end(); ++it1, ++it2) {
                if (it1->first != it2->first) {
                    flag = false;
                    break;
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("map<int, list<int>>");
            } else {
                FAIL("map<int, list<int>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("vector<list<int>>");
        vector<list<int>> vl = {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
        }, vl2;
        try
        {
            bin::Serialize(vl, PRE + "vl.bin");
            bin::Deserialize(vl2, PRE + "vl.bin");
            bool flag = true;
            for (auto it1 = vl.begin(), it2 = vl2.begin(); it1 != vl.end() && it2 != vl2.end(); ++it1, ++it2) {
                for (auto it3 = it1->begin(), it4 = it2->begin(); it3 != it1->end() && it4 != it2->end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("vector<list<int>>");
            } else {
                FAIL("vector<list<int>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("set<list<int>>");
        set<list<int>> sl = {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
        }, sl2;
        try
        {
            bin::Serialize(sl, PRE + "sl.bin");
            bin::Deserialize(sl2, PRE + "sl.bin");
            bool flag = true;
            for (auto it1 = sl.begin(), it2 = sl2.begin(); it1 != sl.end() && it2 != sl2.end(); ++it1, ++it2) {
                for (auto it3 = it1->begin(), it4 = it2->begin(); it3 != it1->end() && it4 != it2->end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("set<list<int>>");
            } else {
                FAIL("set<list<int>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("map<int, vector<pair<list<char>, set<float>>>>");
        map<int, vector<pair<list<char>, set<float>>>> mvl, mvl2;
        for (int i = 0; i < 5; ++i) {
            vector<pair<list<char>, set<float>>> vps;
            for (int j = 0; j < 5; ++j) {
                list<char> lc;
                for (int k = 0; k < 5; ++k) {
                    lc.push_back('a' + k);
                }
                set<float> sf;
                for (int l = 0; l < 5; ++l) {
                    sf.insert(1.1 * l);
                }
                vps.push_back({lc, sf});
            }
            mvl.insert({i, vps});
        }
        try
        {
            bin::Serialize(mvl, PRE + "mvl.bin");
            bin::Deserialize(mvl2, PRE + "mvl.bin");
            bool flag = true;
            for (auto it1 = mvl.begin(), it2 = mvl2.begin(); it1 != mvl.end() && it2 != mvl2.end(); ++it1, ++it2) {
                if (it1->first != it2->first) {
                    flag = false;
                    break;
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    for (auto it5 = it3->first.begin(), it6 = it4->first.begin(); it5 != it3->first.end() && it6 != it4->first.end(); ++it5, ++it6) {
                        if (*it5 != *it6) {
                            flag = false;
                            break;
                        }
                    }
                    for (auto it5 = it3->second.begin(), it6 = it4->second.begin(); it5 != it3->second.end() && it6 != it4->second.end(); ++it5, ++it6) {
                        if (*it5 != *it6) {
                            flag = false;
                            break;
                        }
                    }
                }
            }
            if (flag) {
                PASS("map<int, vector<pair<list<char>, set<float>>>>");
            } else {
                FAIL("map<int, vector<pair<list<char>, set<float>>>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("map<int, list<vector<pair<string, set<pair<char, float>>>>>>");
        map<int, list<vector<pair<string, set<pair<char, float>>>>>> mlvl, mlvl2;
        for (int i = 0; i < 5; ++i) {
            list<vector<pair<string, set<pair<char, float>>>>> lvl;
            for (int j = 0; j < 5; ++j) {
                vector<pair<string, set<pair<char, float>>>> vps;
                for (int k = 0; k < 5; ++k) {
                    set<pair<char, float>> sp;
                    for (int l = 0; l < 5; ++l) {
                        sp.insert({'a' + l, 1.1 * l});
                    }
                    vps.push_back({"hello", sp});
                }
                lvl.push_back(vps);
            }
            mlvl.insert({i, lvl});
        }
        try
        {
            bin::Serialize(mlvl, PRE + "mlvl.bin");
            bin::Deserialize(mlvl2, PRE + "mlvl.bin");
            bool flag = true;
            for (auto it1 = mlvl.begin(), it2 = mlvl2.begin(); it1 != mlvl.end() && it2 != mlvl2.end(); ++it1, ++it2) {
                if (it1->first != it2->first) {
                    flag = false;
                    break;
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    for (auto it5 = it3->begin(), it6 = it4->begin(); it5 != it3->end() && it6 != it4->end(); ++it5, ++it6) {
                        if (it5->first != it6->first) {
                            flag = false;
                            break;
                        }
                        for (auto it7 = it5->second.begin(), it8 = it6->second.begin(); it7 != it5->second.end() && it8 != it6->second.end(); ++it7, ++it8) {
                            if (it7->first != it8->first || it7->second != it8->second) {
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (flag) {
                PASS("map<int, list<vector<pair<string, set<pair<char, float>>>>>>");
            } else {
                FAIL("map<int, list<vector<pair<string, set<pair<char, float>>>>>>");
            }
        }
        ERROR;

        // test user-defined data structure
        BEGIN("struct test");
        test t, t2;
        t.idx = 1;
        t.name = "hello";
        t.data.push_back(1);
        t.data.push_back(2);
        t.data.push_back(3);
        try {
            SerializeBin(t, PRE + "t.bin");
            DeserializeBin(t2, PRE + "t.bin");
            bool flag = true;
            for (auto it1 = t.data.begin(), it2 = t2.data.begin(); it1 != t.data.end() && it2 != t2.data.end(); ++it1, ++it2) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (t.idx == t2.idx && t.name == t2.name && flag) {
                PASS("struct test");
            } else {
                FAIL("struct test");
            }
        }
        ERROR;

        // test unique_ptr
        BEGIN("unique_ptr<map<list<string>, vector<double>>>");
        unique_ptr<map<list<string>, vector<double>>> up, up2;
        up.reset(new map<list<string>, vector<double>>);
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("hello");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.1 * j);
            }
            up->insert({ls, vd});
        }
        try {
            bin::Serialize(up, PRE + "up.bin");
            bin::Deserialize(up2, PRE + "up.bin");
            bool flag = true;
            for (auto it1 = up->begin(), it2 = up2->begin(); it1 != up->end() && it2 != up2->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("unique_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("unique_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        // test shared_ptr
        BEGIN("shared_ptr<map<list<string>, vector<double>>>");
        shared_ptr<map<list<string>, vector<double>>> sp, sp2;
        sp.reset(new map<list<string>, vector<double>>);
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("hello");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.1 * j);
            }
            sp->insert({ls, vd});
        }
        try {
            bin::Serialize(sp, PRE + "sp.bin");
            bin::Deserialize(sp2, PRE + "sp.bin");
            bool flag = true;
            for (auto it1 = sp->begin(), it2 = sp2->begin(); it1 != sp->end() && it2 != sp2->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("shared_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("shared_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        // test weak_ptr
        BEGIN("weak_ptr<map<list<string>, vector<double>>>");
        weak_ptr<map<list<string>, vector<double>>> wp, wp2;
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("world");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.2 * j);
            }
            sp->insert({ls, vd});
        }
        wp = sp;
        wp2 = sp2;
        try {
            bin::Serialize(wp, PRE + "wp.bin");
            bin::Deserialize(wp2, PRE + "wp.bin");
            bool flag = true;
            for (auto it1 = sp->begin(), it2 = wp2.lock()->begin(); it1 != sp->end() && it2 != wp2.lock()->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("weak_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("weak_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        // output total result
        if (pass == total) {
            changeColor(GREEN);
            cout << "[success] " << pass << "/" << total << endl;
            return true;
        } else {
            changeColor(RED);
            cout << "[fail] " << fail << "/" << total << endl;
            return false;
        }
    }

    /// @brief test xml serialization and deserialization with different types
    /// @return true if all tests pass, false otherwise
    bool TestXml() {
        HEAD("xml");

        // test bool
        BEGIN("bool");
        bool b = true, b2;
        try
        {
            xml::Serialize(b, PRE + "b.xml");
            xml::Deserialize(b2, PRE + "b.xml");
            if (b == b2) {
                PASS("bool");
            } else {
                FAIL("bool");
            }
        }
        ERROR;

        // test char
        BEGIN("char");
        char c = 'a', c2;
        try
        {
            xml::Serialize(c, PRE + "c.xml");
            xml::Deserialize(c2, PRE + "c.xml");
            if (c == c2) {
                PASS("char");
            } else {
                FAIL("char");
            }
        }
        ERROR;

        // test int
        BEGIN("int");
        int i = 123456789, i2;
        try
        {
            xml::Serialize(i, PRE + "i.xml");
            xml::Deserialize(i2, PRE + "i.xml");
            if (i == i2) {
                PASS("int");
            } else {
                FAIL("int");
            }
        }
        ERROR;

        // test float
        BEGIN("float");
        float f = 123.456f, f2;
        try
        {
            xml::Serialize(f, PRE + "f.xml");
            xml::Deserialize(f2, PRE + "f.xml");
            if (f == f2) {
                PASS("float");
            } else {
                FAIL("float");
            }
        }
        ERROR;

        // test double
        BEGIN("double");
        double d = 123.456789128192112, d2;
        try
        {
            xml::Serialize(d, PRE + "d.xml");
            xml::Deserialize(d2, PRE + "d.xml");
            if (d == d2) {
                PASS("double");
            } else {
                FAIL("double");
            }
        }
        ERROR;

        // test string
        BEGIN("string");
        string s = "hello world", s2;
        try
        {
            xml::Serialize(s, PRE + "s.xml");
            xml::Deserialize(s2, PRE + "s.xml");
            if (s == s2) {
                PASS("string");
            } else {
                FAIL("string");
            }
        }
        ERROR;

        // test vector
        BEGIN("vector");
        vector<int> v = {1, 2, 3, 4, 5}, v2;
        try
        {
            xml::Serialize(v, PRE + "v.xml");
            xml::Deserialize(v2, PRE + "v.xml");
            bool flag = true;
            for (int i = 0; i < v.size(); i++) {
                if (v[i] != v2[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("vector");
            } else {
                FAIL("vector");
            }
        }
        ERROR;

        // test list
        BEGIN("list");
        list<int> l = {1, 2, 3, 4, 5}, l2;
        try
        {
            xml::Serialize(l, PRE + "l.xml");
            xml::Deserialize(l2, PRE + "l.xml");
            bool flag = true;
            auto it1 = l.begin();
            auto it2 = l2.begin();
            for (; it1 != l.end(); it1++, it2++) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("list");
            } else {
                FAIL("list");
            }
        }
        ERROR;

        // test set
        BEGIN("set");
        set<int> se = {1, 2, 3, 4, 5}, se2;
        try
        {
            xml::Serialize(se, PRE + "se.xml");
            xml::Deserialize(se2, PRE + "se.xml");
            bool flag = true;
            auto it1 = se.begin();
            auto it2 = se2.begin();
            for (; it1 != se.end(); it1++, it2++) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("set");
            } else {
                FAIL("set");
            }
        }
        ERROR;

        // test map
        BEGIN("map");
        map<int, string> m = {{1, "a"}, {2, "b"}, {3, "c"}}, m2;
        try
        {
            xml::Serialize(m, PRE + "m.xml");
            xml::Deserialize(m2, PRE + "m.xml");
            bool flag = true;
            auto it1 = m.begin();
            auto it2 = m2.begin();
            for (; it1 != m.end(); it1++, it2++) {
                if (it1->first != it2->first || it1->second != it2->second) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                PASS("map");
            } else {
                FAIL("map");
            }
        }
        ERROR;

        // test pair
        BEGIN("pair");
        pair<int, string> p = {1, "a"}, p2;
        try
        {
            xml::Serialize(p, PRE + "p.xml");
            xml::Deserialize(p2, PRE + "p.xml");
            if (p.first == p2.first && p.second == p2.second) {
                PASS("pair");
            } else {
                FAIL("pair");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("vector<list<set<int>>>");
        vector<list<set<int>>> vls = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}}, vls2;
        try
        {
            xml::Serialize(vls, PRE + "vls.xml");
            xml::Deserialize(vls2, PRE + "vls.xml");
            bool flag = true;
            for (auto it1 = vls.begin(), it2 = vls2.begin(); it1 != vls.end(); it1++, it2++) {
                auto it3 = it1->begin();
                auto it4 = it2->begin();
                for (; it3 != it1->end(); it3++, it4++) {
                    auto it5 = it3->begin();
                    auto it6 = it4->begin();
                    for (; it5 != it3->end(); it5++, it6++) {
                        if (*it5 != *it6) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            if (flag) {
                PASS("vector<list<set<int>>>");
            } else {
                FAIL("vector<list<set<int>>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("map<int, vector<list<set<int>>>>");
        map<int, vector<list<set<int>>>> mvls = {{1, {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}}}}, mvls2;
        try
        {
            xml::Serialize(mvls, PRE + "mvls.xml");
            xml::Deserialize(mvls2, PRE + "mvls.xml");
            bool flag = true;
            for (auto it1 = mvls.begin(), it2 = mvls2.begin(); it1 != mvls.end(); it1++, it2++) {
                auto it3 = it1->second.begin();
                auto it4 = it2->second.begin();
                for (; it3 != it1->second.end(); it3++, it4++) {
                    auto it5 = it3->begin();
                    auto it6 = it4->begin();
                    for (; it5 != it3->end(); it5++, it6++) {
                        auto it7 = it5->begin();
                        auto it8 = it6->begin();
                        for (; it7 != it5->end(); it7++, it8++) {
                            if (*it7 != *it8) {
                                flag = false;
                                break;
                            }
                        }
                        if (!flag) break;
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
            if (flag) {
                PASS("map<int, vector<list<set<int>>>>");
            } else {
                FAIL("map<int, vector<list<set<int>>>>");
            }
        }
        ERROR;

        // test composed data structure
        BEGIN("map<int, vector<list<set<pair<int, string>>>>>");
        map<int, list<vector<pair<string, set<pair<char, float>>>>>> mlvl, mlvl2;
        for (int i = 0; i < 5; ++i) {
            list<vector<pair<string, set<pair<char, float>>>>> lvl;
            for (int j = 0; j < 5; ++j) {
                vector<pair<string, set<pair<char, float>>>> vps;
                for (int k = 0; k < 5; ++k) {
                    set<pair<char, float>> sp;
                    for (int l = 0; l < 5; ++l) {
                        sp.insert({'a' + l, 1.1 * l});
                    }
                    vps.push_back({"hello", sp});
                }
                lvl.push_back(vps);
            }
            mlvl.insert({i, lvl});
        }
        try
        {
            xml::Serialize(mlvl, PRE + "mlvl.xml");
            xml::Deserialize(mlvl2, PRE + "mlvl.xml");
            bool flag = true;
            for (auto it1 = mlvl.begin(), it2 = mlvl2.begin(); it1 != mlvl.end() && it2 != mlvl2.end(); ++it1, ++it2) {
                if (it1->first != it2->first) {
                    flag = false;
                    break;
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    for (auto it5 = it3->begin(), it6 = it4->begin(); it5 != it3->end() && it6 != it4->end(); ++it5, ++it6) {
                        if (it5->first != it6->first) {
                            flag = false;
                            break;
                        }
                        for (auto it7 = it5->second.begin(), it8 = it6->second.begin(); it7 != it5->second.end() && it8 != it6->second.end(); ++it7, ++it8) {
                            if (it7->first != it8->first || it7->second != it8->second) {
                                flag = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (flag) {
                PASS("map<int, list<vector<pair<string, set<pair<char, float>>>>>>");
            } else {
                FAIL("map<int, list<vector<pair<string, set<pair<char, float>>>>>>");
            }
        }
        ERROR;

        // test user-defined data structure
        BEGIN("struct test");
        test t, t2;
        t.idx = 1;
        t.name = "hello";
        t.data.push_back(1);
        t.data.push_back(2);
        t.data.push_back(3);
        try {
            SerializeXml(t, PRE + "t.xml");
            DeserializeXml(t2, PRE + "t.xml");
            bool flag = true;
            for (auto it1 = t.data.begin(), it2 = t2.data.begin(); it1 != t.data.end() && it2 != t2.data.end(); ++it1, ++it2) {
                if (*it1 != *it2) {
                    flag = false;
                    break;
                }
            }
            if (t.idx == t2.idx && t.name == t2.name && flag) {
                PASS("struct test");
            } else {
                FAIL("struct test");
            }
        }
        ERROR;

        // test unique_ptr
        BEGIN("unique_ptr<map<list<string>, vector<double>>>");
        unique_ptr<map<list<string>, vector<double>>> up, up2;
        up.reset(new map<list<string>, vector<double>>);
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("hello");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.1 * j);
            }
            up->insert({ls, vd});
        }
        try {
            xml::Serialize(up, PRE + "up.xml");
            xml::Deserialize(up2, PRE + "up.xml");
            bool flag = true;
            for (auto it1 = up->begin(), it2 = up2->begin(); it1 != up->end() && it2 != up2->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("unique_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("unique_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        // test shared_ptr
        BEGIN("shared_ptr<map<list<string>, vector<double>>>");
        shared_ptr<map<list<string>, vector<double>>> sp, sp2;
        sp.reset(new map<list<string>, vector<double>>);
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("hello");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.1 * j);
            }
            sp->insert({ls, vd});
        }
        try {
            xml::Serialize(sp, PRE + "sp.xml");
            xml::Deserialize(sp2, PRE + "sp.xml");
            bool flag = true;
            for (auto it1 = sp->begin(), it2 = sp2->begin(); it1 != sp->end() && it2 != sp2->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("shared_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("shared_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        // test weak_ptr
        BEGIN("weak_ptr<map<list<string>, vector<double>>>");
        weak_ptr<map<list<string>, vector<double>>> wp, wp2;
        for (int i = 0; i < 5; ++i) {
            list<string> ls;
            for (int j = 0; j < 5; ++j) {
                ls.push_back("world");
            }
            vector<double> vd;
            for (int j = 0; j < 5; ++j) {
                vd.push_back(1.2 * j);
            }
            sp->insert({ls, vd});
        }
        wp = sp;
        wp2 = sp2;
        try {
            xml::Serialize(wp, PRE + "wp.xml");
            xml::Deserialize(wp2, PRE + "wp.xml");
            bool flag = true;
            for (auto it1 = sp->begin(), it2 = wp2.lock()->begin(); it1 != sp->end() && it2 != wp2.lock()->end(); ++it1, ++it2) {
                for (auto it3 = it1->first.begin(), it4 = it2->first.begin(); it3 != it1->first.end() && it4 != it2->first.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
                for (auto it3 = it1->second.begin(), it4 = it2->second.begin(); it3 != it1->second.end() && it4 != it2->second.end(); ++it3, ++it4) {
                    if (*it3 != *it4) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                PASS("weak_ptr<map<list<string>, vector<double>>>");
            } else {
                FAIL("weak_ptr<map<list<string>, vector<double>>>");
            }
        }
        ERROR;

        if (pass == total) {
            changeColor(GREEN);
            cout << "[success] " << pass << "/" << total << endl;
            return true;
        } else {
            changeColor(RED);
            cout << "[fail] " << fail << "/" << total << endl;
            return false;
        }
    }

    /// @brief test binary serialization and deserialization and test xml serialization and deserialization
    void AllTests() {
        bool ok = TestBin() && TestXml(); // get the result of all tests
        if (ok) {
            changeColor(GREEN);
            cout << "[success] all test pass" << endl;
        } else {
            changeColor(RED);
            cout << "[fail] some test fail" << endl;
        }
    }
}