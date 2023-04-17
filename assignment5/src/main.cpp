#include "fraction.cpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/// @brief Convert bool to string
/// @param b bool value
/// @return "true" if b is true, "false" otherwise
string bool2string(bool b) {
    return b ? "true" : "false";
}

void test() {
    // Test constructors
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction f3(f2);
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f3 = " << f3 << endl;

    // Test operators
    Fraction f4;
    f4 = f1 + f2;
    Fraction f5;
    f5 = f1 - f2;
    Fraction f6;
    f6 = f1 * f2;
    Fraction f7;
    f7 = f1 / f2;
    cout << f1 << " + " << f2 << " = " << f4 << endl;
    cout << f1 << " - " << f2 << " = " << f5 << endl;
    cout << f1 << " * " << f2 << " = " << f6 << endl;
    cout << f1 << " / " << f2 << " = " << f7 << endl;

    // Test comparison operators
    cout << f1 << " < " << f2 << " is " << bool2string((f1 < f2)) << endl;
    cout << f1 << " <= " << f2 << " is " << bool2string((f1 <= f2)) << endl;
    cout << f1 << " == " << f2 << " is " << bool2string((f1 == f2)) << endl;
    cout << f1 << " != " << f2 << " is " << bool2string((f1 != f2)) << endl;
    cout << f1 << " >= " << f2 << " is " << bool2string((f1 >= f2)) << endl;
    cout << f1 << " > " << f2 << " is " << bool2string((f1 > f2)) << endl;

    // Test toDouble and toString
    cout << "f1's toDouble value is " << f1.toDouble() << endl;
    cout << "f2's toDouble value is " << f2.toDouble() << endl;
    cout << "f1's toString value is " << f1.toString() << endl;
    cout << "f2's toString value is " << f2.toString() << endl;

    // Test input and output
    Fraction f8;
    string input = "8/9";
    istringstream iss(input);
    iss >> f8;
    cout << "Input as " << input << ", " << "f8 = " << f8 << endl;

    // Test readDecimalString
    Fraction f9;
    string doubleStr = "1.414";
    f9.readDecimalString(doubleStr);
    cout << "Input from string " << doubleStr << ", " << "f9 = " << f9 << endl;
}

int main() {
    test();
}