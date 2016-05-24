#include <sstream>
#include <cassert>
#include "BigInteger.h"


BigInteger::BigInteger()//empty constructor initializes zero
{
	number = "0";
	sign = false;
}

//-------------------------------------------------------------
BigInteger::BigInteger(string s)//"string" constructor
{
	if (isdigit(s[0])){
		setNumber(s);
		sign = false;
	}
	else{
		setNumber(s.substr(1));
		sign = (s[0] == '-');
	}
}

//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin)//"string" constructor
{
	setNumber(s);
	setSign(sin);
}

//-------------------------------------------------------------
BigInteger::BigInteger(int n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	if (isdigit(s[0])){
		setNumber(s);
		sign = false;
	}
	else{
		setNumber(s.substr(1));
		sign = (s[0] == '-');
	}
}

//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}

//-------------------------------------------------------------
const string& BigInteger::getNumber() const
{
	return number;
}

//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}

//-------------------------------------------------------------
const bool& BigInteger::getSign() const
{
	return sign;
}

//-------------------------------------------------------------
BigInteger BigInteger::absolute() const
{
	return BigInteger( getNumber() );
}

//-------------------------------------------------------------
void BigInteger::operator= (BigInteger& b)
{
	setNumber(b.getNumber());
	setSign(b.getSign());
}

//-------------------------------------------------------------
bool BigInteger::operator == (BigInteger& b)
{
	return equals((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator!= (BigInteger& b)
{
	return ! equals((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator > (BigInteger& b)
{
	return greater((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator < (BigInteger& b)
{
	return less((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator >= (BigInteger& b)
{
	return greater((*this), b) || equals((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator <= (BigInteger& b)
{
	return less((*this), b) || equals((*this), b);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator ++() // prefix
{
	(*this) = (*this) + 1;
	return (*this);
}

//-------------------------------------------------------------
BigInteger  BigInteger::operator ++(int) // postfix
{
	BigInteger temp = (*this);
	(*this) = (*this) + 1;
	return temp;
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator --() // prefix
{
	(*this) = (*this) - 1;
	return (*this);
}

//-------------------------------------------------------------
BigInteger  BigInteger::operator --(int) // postfix
{
	BigInteger temp = (*this);
	(*this) = (*this) - 1;
	return temp;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator + (const BigInteger& b)
{
	BigInteger ans;
	if (getSign() == b.getSign()){
		ans.setNumber(add(getNumber(), b.getNumber()));
		ans.setSign(getSign());
	}
	else{
		if (absolute() > b.absolute()){
			ans.setNumber(subtract(getNumber(), b.getNumber()));
			ans.setSign(getSign());
		}
		else{
			ans.setNumber(subtract(b.getNumber(), getNumber()));
			ans.setSign(b.getSign());
		}
	}
	if (ans.getNumber() == "0")
		ans.setSign(false);

	return ans;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator - (const BigInteger& b)
{
	BigInteger ans = b;
	ans.setSign(!ans.getSign());
	return (*this) + ans;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator * (const BigInteger& b)
{
	BigInteger ans;
	ans.setNumber(multiply(getNumber(), b.getNumber()));
	ans.setSign(getSign() != b.getSign());
	if (ans.getNumber() == "0")
		ans.setSign(false);

	return ans;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator / (const BigInteger& b)
{
	if (getNumber() < b.getNumber())	return 0;
	BigInteger ans;
	bool bSign = (getSign() != b.getSign());
	string r_str = this->getNumber().substr(0, b.getNumber().length());
	const string& dividend_str = getNumber();
	const string& divisor_str = b.getNumber();
	
	BigInteger r(r_str);
	BigInteger divisor(divisor_str);

	int curPos = r_str.length() - 1;
	while (curPos < dividend_str.length()){
		int tmpR = 0;
		while (r >= divisor){
			r = r - divisor;
			tmpR++;
		}
		ans = ans * 10 + tmpR;
		if (++curPos == divisor_str.length())
			break;
		r = r * 10 + dividend_str[curPos] - '0';
	}

	ans.setSign(bSign);
	return ans;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator % (const BigInteger& b)
{
	BigInteger ans;
	ans = (*this) - ((*this) / b) * b;

	return ans;
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator += (const BigInteger& b)
{
	(*this) = (*this) + b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator -= (const BigInteger& b)
{
	(*this) = (*this) - b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator *= (const BigInteger& b)
{
	(*this) = (*this) * b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator /= (const BigInteger& b)
{
	(*this) = (*this) / b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator %= (const BigInteger& b)
{
	(*this) = (*this) % b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator [] (int n)
{
	assert(n >= 0);
	return *(this + (n*sizeof(BigInteger)));
}

//-------------------------------------------------------------
BigInteger BigInteger::operator -() // unary minus sign
{
	return (*this) * -1;
}

//-------------------------------------------------------------
BigInteger::operator string()
{
	string signedString = (getSign()) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}

//-------------------------------------------------------------
bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.getNumber() == n2.getNumber() && n1.getSign() == n2.getSign();
}

//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if (sign1 && !sign2)
		return true;
	else if (!sign1 && sign2)
		return false;
	else if (!sign1){
		if (n1.getNumber().length() == n2.getNumber().length())
			return n1.getNumber() < n2.getNumber();
		else
			return n1.getNumber().length() < n2.getNumber().length();
	}
	else{
		if (n1.getNumber().length() == n2.getNumber().length())
			return n1.getNumber() > n2.getNumber();
		else
			return n1.getNumber().length() > n2.getNumber().length();
	}

}

//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return !equals(n1, n2) && !less(n1, n2);
}

//-------------------------------------------------------------
string BigInteger::add(string number1, string number2)
{
	int length1 = number1.length(), length2 = number2.length();
	int length = length1 > length2 ? length1 : length2;
	string res(length, '0');
	int carry = 0, index = 0;
	while (index < length1 || index < length2){
		if (index < length1)
			carry += number1[length1 - index - 1] - '0';
		if (index < length2)
			carry += number2[length2 - index - 1] - '0';
		res[length - index - 1] = carry % 10 + '0';
		carry /= 10;
		index++;
	}
	if (carry == 1)
		res.insert(0, 1, '1');

	return res;
}

//-------------------------------------------------------------
string BigInteger::subtract(string number1, string number2)
{
	string ans = number1;
	int len1 = ans.length(), len2 = number2.length();
	int carry = 0, i = 0, h = 0;
	
	for (i = 0; i < len2; i++, carry = 0){
		if (ans[len1 - i - 1] < number2[len2 - i - 1]){
			for (h = len1 - i - 2; h >= 0; h--){
				if (ans[h] == '0')
					ans[h] = '9';
				else if (ans[h] > '0'){
					ans[h]--;
					carry = 10;
					break;
				}
			}
		}
		ans[len1 - i - 1] = carry + ans[len1 - i - 1] - number2[len2 - i - 1] + '0';
	}
	for (i = 0; i < len1 && ans[i] == '0'; i++);
	
	return i == len1 ? "0" : ans.substr(i);
}

//-------------------------------------------------------------
string BigInteger::multiply(string number1, string number2)
{
	if (number1.size() == 0 || number2.size() == 0 || number1 == "0" || number2 == "0")return "0";
	string res(number1.size() + number2.size(), '0');
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	for (int i = 0; i < number1.size(); i++){
		int carry = 0;
		for (int j = 0; j < number2.size(); j++){
			int digit = res[i + j] - '0';
			int num = (number1[i] - '0') * (number2[j] - '0');
			int tmp = digit + num + carry;
			res[i + j] = (tmp % 10) + '0';
			carry = tmp / 10;
		}
		int index = i + number2.size();
		while (carry){
			int digit = res[index] - '0';
			int tmp = digit + carry;
			res[index] = (tmp % 10) + '0';
			carry = tmp / 10;
		}
	}
	while (true){
		if (res[res.size() - 1] == '0' && res.size() > 1)
			res.erase(res.size() - 1, 1);
		else
			break;
	}

	reverse(res.begin(), res.end());
	return res;
}

