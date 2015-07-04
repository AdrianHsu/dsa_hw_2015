#include <iostream>
#include <cctype> // to ensure that string member is digit
#include <cmath> // to get max or min
#include <string>

#include "biginteger_for_binary.h"
using namespace std;

BigInteger::BigInteger()
{
	for (int i = 0; i < digits; i++)
		a[i] = 0;
	length = 0;
}
BigInteger::BigInteger(const int& input)
{
	for (int i = 0; i < digits; i++)
		a[i] = 0;
	length = 0;

	//input is passed by reference with const,
	//therefore can't be modified.
	if (input != 0)
	{
		int tmp_1 = input;
		int tmp_2 = input;
		int len = 0;
		//count length of input
		while(tmp_1 != 0)
		{
			tmp_1 /= 10;
			len++;
		}
		for (int i = 0; tmp_2 != 0 && i < len; i++)
		{
			a[i] = tmp_2 % 10;
			tmp_2 /= 10;
		}
		length = len;
	}
}
BigInteger::BigInteger(const string& input)
{
	for (int i = 0; i < digits; i++)
		a[i] = 0;
	length = 0;

	const int len = input.length();
	//string stores digits in an increasing manner
	for (int i = 0; i <= len - 1; i++)
	{
		if (isdigit( input[len - 1 - i] ))
			a[i] = input[len - 1 - i] - '0';
	}

	length = input.length();
}
BigInteger::BigInteger(const BigInteger& input)
{
	for (int i = 0; i < digits; i++)
		a[i] = 0;
	length = 0;

	if (&input != this)
	{
		for (int i = 0; i < digits; i++)
			a[i] = input.a[i];
		length = input.length;
	}
}
BigInteger::~BigInteger()
{}
bool BigInteger::operator<(const BigInteger& input) const
{
	for (int i = digits - 1; i >= 0; i--)
		if (a[i] < input.a[i])
			return true;
		else if (a[i] > input.a[i])
			return false;
	//equal
	return false;
}
const BigInteger BigInteger::operator-(const BigInteger& input) const
{
	int carry = 0;
	BigInteger temp;
	//*this must be bigger than input, for the result is positive or zero
	for (int i = 0; i < length; i++)
	{
		if (a[i] - carry >= input.a[i])
		{
			temp.a[i] = a[i] - carry - input.a[i];
			carry = 0;
		}
		else
		{
			temp.a[i] = a[i] + 10 - carry - input.a[i];
			carry = 1;
		}
	}
	temp.findlen();
	return temp;
}
const BigInteger BigInteger::operator*(const BigInteger& input) const
{
	BigInteger temp, total;

	for (int i = 0 ; i < input.length; i++)
	{
		//(*this) is assigned to temp everytime loops
		temp = *this;
		temp *= input.a[i];

		if (i > 0)//if i == 0, then temp doesn't need to move 
		{	//temp *= pow(10, i)
			for (int k = temp.length - 1; k >= 0; k-- )
			{
				temp.a[k + i] = temp.a[k];
				temp.a[k] = 0;
			}
		}
		temp.findlen();
		total = (total + temp);
		total.findlen();
	}

	return total;
}
BigInteger& BigInteger::operator*=(int input)
{
	if (input == 0)
	{
		for (int i = 0; i < length; i++)
			a[i] = 0;
		length = 0;
		return *this;
	}
	if (input <= 9)
	{
		int carry = 0;
		//it's possible to be length + 1
		//e.g. 99 * 9 = 891, length: 2 changes to 3
		for (int i = 0; i < length + 1; i++)
		{
			a[i] *= input;
			a[i] += carry;
			if (a[i] > 9)
			{
				carry = a[i] / 10;
				a[i] %= 10;
			}
			else
				carry = 0;
		}
	}
	(*this).findlen();
	return *this;
}
BigInteger& BigInteger::operator/=(int input)
{
	BigInteger ratio;
	BigInteger _this(*this); // this BigInteger cannot be modified
	BigInteger _input(input); // input cannot be modified, since it's const
	int carry, power;

	//if _input > _this, then dividing process is over
	while (_input < _this || _input == _this)
	{
		power = 0;
		carry = 0;

		while (_input < _this)
		{
			for (int k = _input.length - 1; k >= 0; k-- )
			{
				_input.a[k + 1] = _input.a[k];
				_input.a[k] = 0;
			}
			power++;
			_input.length++;
		}
		if (!(_input == _this))
		{
			for (int k = 0; k < _input.length - 1; k++ )
			{
				_input.a[k] = _input.a[k + 1];
				_input.a[k + 1] = 0;
			}
			power--;
			_input.length--;
		}
		while (_input < _this || _input == _this)
		{
			_this = (_this - _input);
			carry++;
		}
		ratio.a[power] = carry;

		_this.findlen();
		_input = input; //_input return to the original value everytime loops
	}
	ratio.findlen();
	(*this) = ratio;
	return *this;

}
BigInteger& BigInteger::operator=(const BigInteger& input)
{
	if (&input != this) //avoid self-assignment
	{
		for (int i = 0; i < digits; i++)
		{
			if (input.a[i] == 0)
				a[i] = 0;
			else
				a[i] = input.a[i];
			/*a[i] = 0;
			for(int i = 0; i < input.length; i++)
			a[i] = input.a[i];*/
			/*Program received signal SIGSEGV, Segmentation fault.
				0x00401f6d in operator= (input=..., this=0x28e284)
				at biginteger_for_binary.cpp:245
				245                             a[i] = input.a[i];*/
		}
		length = input.length;
	}
	return *this;
}
const BigInteger BigInteger::operator%(const BigInteger& input) const
{

	BigInteger ratio;
	BigInteger _this(*this); // this BigInteger cannot be modified
	BigInteger _input(input); // input cannot be modified, since it's const
	int carry, power;

	//if _input > _this, then dividing process is over
	while (_input < _this || _input == _this) 
	{
		power = 0;
		carry = 0;

		while (_input < _this)
		{
			for (int k = _input.length - 1; k >= 0; k-- )
			{
				_input.a[k + 1] = _input.a[k];
				_input.a[k] = 0;
			}
			power++;
			_input.length++;
		}
		if (!(_input == _this))
		{
			for (int k = 0; k < _input.length - 1; k++ )
			{
				_input.a[k] = _input.a[k + 1];
				_input.a[k + 1] = 0;
			}
			power--;
			_input.length--;
		}
		while (_input < _this || _input == _this)
		{
			_this = (_this - _input);
			carry++;
		}
		ratio.a[power] = carry;

		_this.findlen();
		_input = input; //_input return to the original value everytime loops
	}
	ratio.findlen();

	return _this;
}
BigInteger BigInteger::operator+(const BigInteger& input) const
{
	int carry = 0;
	BigInteger temp;

	for (int i = 0; i < max(length, input.length) + 1; i++) //it's possible that i to be length + 1
	{
		temp.a[i] = a[i] + input.a[i] + carry;
		if (temp.a[i] > 9)
		{
			temp.a[i] %= 10;
			carry = 1;
		} else
			carry = 0;
	}
	temp.findlen();
	return temp;
}
BigInteger BigInteger::operator/(const BigInteger& input) const
{
	//prevent "divide by zero" exception
	BigInteger divide_by_zero(0);
	if (input == 0) return divide_by_zero;
	BigInteger ratio;
	BigInteger _this(*this); // this BigInteger cannot be modified
	BigInteger _input(input); // input cannot be modified, since it's const
	int carry, power;

	//if _input > _this, then dividing process is over
	while (_input < _this || _input == _this)
	{
		power = 0; //power is for ratio digits
		carry = 0; //carry is for sum of ratio in particular digit

		while (_input < _this) 
		{	// multiplies by 10 everytime
			for (int k = _input.length - 1; k >= 0; k-- )
			{
				_input.a[k + 1] = _input.a[k];
				_input.a[k] = 0;
			}
			power++;
			_input.length++;
		}
		if (!(_input == _this)) //e.g. 1000 == 10 * 100
		{
			for (int k = 0; k < _input.length - 1; k++ )
			{
				_input.a[k] = _input.a[k + 1];
				_input.a[k + 1] = 0;
			}
			power--;
			_input.length--;
		}
		while (_input < _this || _input == _this)
		{
			_this = (_this - _input);
			carry++;
		}
		ratio.a[power] = carry;

		_this.findlen();
		_input = input; //_input return to the original value everytime loops

	}
	ratio.findlen();
	return ratio;
}
bool BigInteger::operator==(const BigInteger& input) const
{
	for (int i = digits - 1; i >= 0; i--)
		if (a[i] < input.a[i])
			return false;
		else if (a[i] > input.a[i])
			return false;
	//equal
	return true;
}
void BigInteger::findlen()
{
	for (int i = digits - 1; i >= 0; i--)
	{
		if (a[i] != 0)
		{
			length = i + 1;
			return;
		}
	}
	length = 0;
}
bool BigInteger::iseven()
{
	if (a[0] % 2 == 0) return true;
	else return false;
}
bool BigInteger::iszero()
{
	if (length == 0) return true;
	else return false;
}
ostream& operator<<(ostream& out, const BigInteger& input)
{
	if (input.length == 0)
	{
		out << 0;
		return out;
	}
	for (int i = input.length - 1; i >= 0; i--)
		out << input.a[i];
	return out;
}
