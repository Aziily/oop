#include "bin.hpp"
#include "xml.hpp"

using namespace std;

namespace Tester {
    static const string PRE = "../output/";

    static const string WHITE = "\033[0m";
    static const string RED = "\033[31m";
    static const string GREEN = "\033[32m";
    static const string CYAN = "\033[36m";
    static const string YELLOW = "\033[33m";
    static const string PURPLE = "\033[35m";

    void changeColor(string color) {
        cout << color;
    }

    bool TestBin() {
        changeColor(CYAN);
        cout << "========================================" << endl;
        cout << "Begin test of binary serialization" << endl;
        cout << "========================================" << endl;
        int pass = 0, fail = 0, total = 0;

        //test bool
        changeColor(YELLOW);
        cout << "[begin] test bool" << endl;
        bool b = true, b2;
        try
        {
            bin::Serialize(b, PRE + "b.bin");
            bin::Deserialize(b2, PRE + "b.bin");
            if (b == b2) {
                changeColor(GREEN);
                cout << "[pass] test bool" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test bool" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test char
        changeColor(YELLOW);
        cout << "[begin] test char" << endl;
        char c = 'a', c2;
        try
        {
            bin::Serialize(c, PRE + "c.bin");
            bin::Deserialize(c2, PRE + "c.bin");
            if (c == c2) {
                changeColor(GREEN);
                cout << "[pass] test char" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test char" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test int
        changeColor(YELLOW);
        cout << "[begin] test int" << endl;
        int num = 123456789, num2;
        try
        {
            bin::Serialize(num, PRE + "num.bin");
            bin::Deserialize(num2, PRE + "num.bin");
            if (num == num2) {
                changeColor(GREEN);
                cout << "[pass] test int" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test int" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test float
        changeColor(YELLOW);
        cout << "[begin] test float" << endl;
        float f = 188.888888, f2;
        try
        {
            bin::Serialize(f, PRE + "f.bin");
            bin::Deserialize(f2, PRE + "f.bin");
            if (f == f2) {
                changeColor(GREEN);
                cout << "[pass] test float" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test float" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }
        

        //test double
        changeColor(YELLOW);
        cout << "[begin] test double" << endl;
        double d = 123456789.123456789, d2;
        try
        {
            bin::Serialize(d, PRE + "d.bin");
            bin::Deserialize(d2, PRE + "d.bin");
            if (d == d2) {
                changeColor(GREEN);
                cout << "[pass] test double" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test double" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        
        //test string
        changeColor(YELLOW);
        cout << "[begin] test string" << endl;
        string str = "Hello World!", str2;
        try
        {
            bin::Serialize(str, PRE + "str.bin");
            bin::Deserialize(str2, PRE + "str.bin");
            if (str == str2) {
                changeColor(GREEN);
                cout << "[pass] test string" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test string" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test list
        changeColor(YELLOW);
        cout << "[begin] test list" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test list" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test list" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test set
        changeColor(YELLOW);
        cout << "[begin] test set" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test set" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test set" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test vector
        changeColor(YELLOW);
        cout << "[begin] test vector" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test vector" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test vector" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test map
        changeColor(YELLOW);
        cout << "[begin] test map" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test map" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test map" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test pair
        changeColor(YELLOW);
        cout << "[begin] test pair" << endl;
        pair<int, int> p = {1, 1}, p2;
        try
        {
            bin::Serialize(p, PRE + "p.bin");
            bin::Deserialize(p2, PRE + "p.bin");
            if (p.first == p2.first && p.second == p2.second) {
                changeColor(GREEN);
                cout << "[pass] test pair" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test pair" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test composed data structure
        changeColor(YELLOW);
        cout << "[begin] test map<int, list<int>>" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test map<int, list<int>>" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test map<int, list<int>>" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test composed data structure
        changeColor(YELLOW);
        cout << "[begin] test vector<list<int>>" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test vector<list<int>>" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test vector<list<int>>" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test composed data structure
        changeColor(YELLOW);
        cout << "[begin] test set<list<int>>" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test set<list<int>>" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test set<list<int>>" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test composed data structure
        changeColor(YELLOW);
        cout << "[begin] test map<int, set<int>>" << endl;     
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
                changeColor(GREEN);
                cout << "[pass] test map<int, vector<pair<list<char>, set<float>>>>" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test map<int, vector<pair<list<char>, set<float>>>>" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

        //test composed data structure
        changeColor(YELLOW);
        cout << "[begin] test map<int, list<vector<pair<string, set<pair<char, float>>>>>>" << endl;
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
                changeColor(GREEN);
                cout << "[pass] test map<int, list<vector<pair<string, set<pair<char, float>>>>>>" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test map<int, list<vector<pair<string, set<pair<char, float>>>>>>" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }

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

    bool TestXml() {
        changeColor(CYAN);
        cout << "========================================" << endl;
        cout << "Begin test of xml serialization" << endl;
        cout << "========================================" << endl;
        int pass = 0, fail = 0, total = 0;

        //test basic data structure
        changeColor(YELLOW);
        cout << "[begin] test int" << endl;
        int i = 123456789, i2;
        try
        {
            xml::Serialize(i, PRE + "i.xml");
            xml::Deserialize(i2, PRE + "i.xml");
            if (i == i2) {
                changeColor(GREEN);
                cout << "[pass] test int" << endl;
                pass++;
                total++;
            } else {
                changeColor(RED);
                cout << "[fail] test int" << endl;
                fail++;
                total++;
            }
        }
        catch(const std::exception& e)
        {
            changeColor(RED);
            std::cerr << "[fail] " << e.what() << '\n';
            fail++;
            total++;
        }


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
}