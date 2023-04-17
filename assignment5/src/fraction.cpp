#include <iostream>
using namespace std;

/// @brief Fraction class
class Fraction {
private:
    int numerator;      // numerator
    int denominator;    // denominator

private:
    /// @brief GCD
    /// @param a one number
    /// @param b another number
    /// @return GCD of a and b
    int gcd(int a, int b) { 
        if (a == 0) return b;
        return gcd(b % a, a);
    }

    /// @brief Simplify the fraction
    void simplify() {
        // get the GCD of numerator and denominator
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        // make sure the denominator is positive
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

    /// @brief Check if the denominator is zero
    void checkZero() {
        if (denominator == 0) {
            cout << "Denominator cannot be zero!" << endl;
            exit(1); // exit the program
        }
    }

public:
    /// @brief Constructor with numerator and denominator
    /// @param n numerator
    /// @param d denominator
    Fraction(int n, int d) {
        numerator = n;
        denominator = d;
        simplify();
        checkZero();
    }

    /// @brief Constructor base
    Fraction() {
        numerator = 0;
        denominator = 1;
    }

    /// @brief Copy constructor
    /// @param f another fraction
    Fraction(Fraction &f) {
        numerator = f.numerator;
        denominator = f.denominator;
        simplify();
        checkZero();
    }

public:
    /// @brief Overload the operator +
    /// @param f1 one fraction
    /// @param f2 another fraction
    /// @return the result of f1 + f2
    friend Fraction operator+(const Fraction &f1, const Fraction &f2) {
        Fraction f;
        f.numerator = f1.numerator * f2.denominator + f1.denominator * f2.numerator;
        f.denominator = f1.denominator * f2.denominator;
        f.simplify();
        f.checkZero();
        return f;
    }

    /// @brief Overload the operator -
    /// @param f1 one fraction
    /// @param f2 another fraction
    /// @return the result of f1 - f2
    friend Fraction operator-(const Fraction &f1, const Fraction &f2) {
        Fraction f;
        f.numerator = f1.numerator * f2.denominator - f1.denominator * f2.numerator;
        f.denominator = f1.denominator * f2.denominator;
        f.simplify();
        f.checkZero();
        return f;
    }

    /// @brief Overload the operator *
    /// @param f1 one fraction
    /// @param f2 another fraction
    /// @return the result of f1 * f2
    friend Fraction operator*(const Fraction &f1, const Fraction &f2) {
        Fraction f;
        f.numerator = f1.numerator * f2.numerator;
        f.denominator = f1.denominator * f2.denominator;
        f.simplify();
        f.checkZero();
        return f;
    }

    /// @brief Overload the operator /
    /// @param f1 one fraction
    /// @param f2 another fraction
    /// @return the result of f1 / f2
    friend Fraction operator/(const Fraction &f1, const Fraction &f2) {
        Fraction f;
        f.numerator = f1.numerator * f2.denominator;
        f.denominator = f1.denominator * f2.numerator;
        f.simplify();
        f.checkZero();
        return f;
    }

    /// @brief Overload the operator +=
    /// @param f another fraction
    /// @return the result of this + f
    Fraction operator+=(const Fraction &f) {
        numerator = numerator * f.denominator + denominator * f.numerator;
        denominator = denominator * f.denominator;
        simplify();
        checkZero();
        return *this;
    }

    /// @brief Overload the operator -=
    /// @param f another fraction
    /// @return the result of this - f
    Fraction operator-=(const Fraction &f) {
        numerator = numerator * f.denominator - denominator * f.numerator;
        denominator = denominator * f.denominator;
        simplify();
        checkZero();
        return *this;
    }

    /// @brief Overload the operator *=
    /// @param f another fraction
    /// @return the result of this * f
    Fraction operator*=(const Fraction &f) {
        numerator = numerator * f.numerator;
        denominator = denominator * f.denominator;
        simplify();
        checkZero();
        return *this;
    }

    /// @brief Overload the operator /=
    /// @param f another fraction
    /// @return the result of this / f
    Fraction operator/=(const Fraction &f) {
        numerator = numerator * f.denominator;
        denominator = denominator * f.numerator;
        simplify();
        checkZero();
        return *this;
    }

    /// @brief Overload the operator =
    /// @param f another fraction
    /// @return make this fraction equal to f
    Fraction operator=(const Fraction &f) {
        numerator = f.numerator;
        denominator = f.denominator;
        simplify();
        checkZero();
        return *this;
    }

public:
    /// @brief Extracctor for stream
    /// @param os output stream
    /// @param f fraction
    /// @return output stream
    friend ostream& operator<< (ostream &os, Fraction &f) {
        if (f.numerator == 0) return os << "0";
        else if (f.denominator == f.numerator) return os << "1";
        else if (f.denominator == 1) return os << to_string(f.numerator);
        else return os << f.toString();
    }

    /// @brief Insertor for stream
    /// @param is input stream
    /// @param f fraction
    /// @return input stream
    friend istream& operator>> (istream &is, Fraction &f) {
        Fraction temp;
        char c;
        is >> temp.numerator >> c >> temp.denominator;
        if (c != '/') {
            cout << "Invalid input!" << endl;
            return is;
        }
        f.numerator = temp.numerator;
        f.denominator = temp.denominator;
        f.simplify();
        f.checkZero();
        return is;
    }

public:
    /// @brief Overload the operator ==
    /// @param f another fraction
    /// @return true if this fraction equals to f
    bool operator==(const Fraction &f) {
        return numerator == f.numerator && denominator == f.denominator;
    }

    /// @brief Overload the operator !=
    /// @param f another fraction
    /// @return true if this fraction does not equal to f
    bool operator!=(const Fraction &f) {
        return numerator != f.numerator || denominator != f.denominator;
    }

    /// @brief Overload the operator >
    /// @param f another fraction
    /// @return true if this fraction is greater than f
    bool operator>(const Fraction &f) {
        return numerator * f.denominator > denominator * f.numerator;
    }

    /// @brief Overload the operator <
    /// @param f another fraction
    /// @return true if this fraction is less than f
    bool operator<(const Fraction &f) {
        return numerator * f.denominator < denominator * f.numerator;
    }

    /// @brief Overload the operator >=
    /// @param f another fraction
    /// @return true if this fraction is greater than or equal to f
    bool operator>=(const Fraction &f) {
        return numerator * f.denominator >= denominator * f.numerator;
    }

    /// @brief Overload the operator <=
    /// @param f another fraction
    /// @return true if this fraction is less than or equal to f
    bool operator<=(const Fraction &f) {
        return numerator * f.denominator <= denominator * f.numerator;
    }

public:
    /// @brief Set the numerator
    /// @param n numerator
    void setNumerator(int n) {
        numerator = n;
        simplify();
        checkZero();
    }

    /// @brief Set the denominator
    /// @param d denominator
    void setDenominator(int d) {
        denominator = d;
        simplify();
        checkZero();
    }

    /// @brief Get the numerator
    /// @return numerator
    int getNumerator() {
        return numerator;
    }

    /// @brief Get the denominator
    /// @return denominator
    int getDenominator() {
        return denominator;
    }

public:
    /// @brief Convert to double
    /// @return double
    double toDouble() {
        return (double) numerator / denominator;
    }

    /// @brief Convert to string
    /// @return string
    string toString() {
        return to_string(numerator) + "/" + to_string(denominator);
    }

    /// @brief Convert to decimal string
    /// @param s decimal string
    void readDecimalString(string s) {
        int i = 0;
        int n = 0;
        int d = 1;
        // read the integer part
        while (s[i] != '.') {
            n = n * 10 + s[i] - '0';
            i++;
        }
        i++;
        // read the point part
        while (s[i] != '\0') {
            n = n * 10 + s[i] - '0';
            d *= 10;
            i++;
        }
        numerator = n;
        denominator = d;
        simplify();
        checkZero();
    }
    
};