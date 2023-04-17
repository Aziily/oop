#include "vector.hpp"

string bool2str(bool b) {
    return b ? "true" : "false";
}

void test() {
    // test constructor and destructor
    cout << "test constructor" << endl;
    Vector<int> v1;
    Vector<int> v2(10);
    v2.push_back(1);
    Vector<int> v3(v2);
    cout << "v1: default constructor" << endl;
    v1.print();
    cout << "v2: constructor with size" << endl;
    v2.print();
    cout << "v3: copy constructor" << endl;
    v3.print();
    delete &v2;
    delete &v3;
    cout << endl;

    // test operator[] and at()
    cout << "test operator[] and at()" << endl;
    cout << "push 1, 2, 3 into v1" << endl;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    cout << v1[1] << endl;
    cout << v1.at(1) << endl;

    cout << "test out_of_range exception" << endl;
    try {
        cout << v1.at(3) << endl;
    } catch (out_of_range &e) {
        cout << e.what() << endl;
    }
    cout << endl;

    // test size()
    cout << "test size()" << endl;
    cout << v1.size() << endl;
    v1.print();
    cout << endl;

    // test push_back() and pop_back() 
    cout << "test push_back() and pop_back()" << endl;
    cout << "push 4 into v1" << endl;
    v1.push_back(4);
    v1.print();
    cout << "pop_back() from v1" << endl;
    cout << v1.pop_back() << endl;
    v1.print();
    cout << endl;

    // test resize()
    cout << "test resize()" << endl;
    cout << "push 5, 6 into v1" << endl;
    v1.push_back(5);
    v1.push_back(6);
    v1.print();
    cout << "resize v1 to 3" << endl;
    v1.resize(3);
    v1.print();
    cout << "resize v1 to 10" << endl;
    v1.resize(10);
    v1.print();
    cout << endl;

    // test deleteAt()
    cout << "test deleteAt()" << endl;
    v1.print();
    cout << "delete v1[1]" << endl;
    v1.deleteAt(1);
    v1.print();
    cout << endl;

    // test empty() and clear()
    cout << "test empty() and clear()" << endl;
    cout << "before clear:" << endl;
    v1.print();
    cout << bool2str(v1.empty()) << endl;
    cout << "after clear:" << endl;
    v1.clear();
    cout << bool2str(v1.empty()) << endl;
    v1.print();
    cout << endl;
}

int main() {
    test();
    return 0;
}