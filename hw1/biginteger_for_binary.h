#ifndef BIGINTEGER_FOR_BINARY

#define BIGINTEGER_FOR_BINARY

class BigInteger {
public:
	static const int digits = 300; //(EXTRA)maximum is 256, therefore choose 300
	/*GIVEN SOURCE CODE*/
	BigInteger();
	BigInteger(const int&);
	BigInteger(const std::string&);
	BigInteger(const BigInteger&);
	~BigInteger();

	bool operator<(const BigInteger&) const;
	const BigInteger operator-(const BigInteger&) const; //premise: input isn't negative
	const BigInteger operator*(const BigInteger&) const;
	BigInteger& operator*=(int); //only in 0 - 9, since that gcd_by_binary use only "2"
	BigInteger& operator/=(int);
	BigInteger& operator=(const BigInteger&);
	bool iseven();
	bool iszero();
	
	friend std::ostream& operator<<(std::ostream&, const BigInteger&);

	/*EXTRA SOURCE CODE*/
	BigInteger operator+(const BigInteger&) const;
	BigInteger operator/(const BigInteger&) const;
	const BigInteger operator%(const BigInteger&) const;
	bool operator==(const BigInteger&) const;
	
	void findlen();
	int a[digits];//a[] stands for biginteger array
	int length; //length is the amount of digits a[] stored



};
#endif