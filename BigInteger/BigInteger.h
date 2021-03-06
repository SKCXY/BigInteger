#ifndef _BIG_INTEGER_H_
#define _BIG_INTEGER_H_

#include <string>
using namespace std;


class BigInteger{
private:
	string number;
	bool sign;
public:
	BigInteger();// empty constructor initializes zero
	BigInteger(string s);//
	BigInteger(string s, bool sin);
	BigInteger(int n);
	void setNumber(string s);
	const string& getNumber() const;// retrieves the number
	void setSign(bool s);
	const bool& getSign() const;
	BigInteger absolute() const;// returns the absolute value
	void operator= (BigInteger& b);
	bool operator== (BigInteger& b);
	bool operator!= (BigInteger& b);
	bool operator > (BigInteger& b);
	bool operator < (BigInteger& b);
	bool operator >= (BigInteger& b);
	bool operator <= (BigInteger& b);
	BigInteger& operator ++(); // prefix
	BigInteger  operator ++(int); // postfix
	BigInteger& operator --(); // prefix
	BigInteger  operator --(int); // postfix
	BigInteger operator + (const BigInteger& b);
	BigInteger operator - (const BigInteger& b);
	BigInteger operator * (const BigInteger& b);
	BigInteger operator / (const BigInteger& b);
	BigInteger operator % (const BigInteger& b);
	BigInteger& operator += (const BigInteger& b);
	BigInteger& operator -= (const BigInteger& b);
	BigInteger& operator *= (const BigInteger& b);
	BigInteger& operator /= (const BigInteger& b);
	BigInteger& operator %= (const BigInteger& b);
	BigInteger& operator [] (int n);
	BigInteger operator -(); // unary minus sign
	operator string(); // for conversion from BigInteger to string
private:
	bool equals(BigInteger n1, BigInteger n2);
	bool less(BigInteger n1, BigInteger n2);
	bool greater(BigInteger n1, BigInteger n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string number1, string number2);
	pair<string, long long> divide(string n, long long den);
};


#endif