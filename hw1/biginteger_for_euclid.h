#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

class BigInteger{
public:
	static const int digits = 300; //(EXTRA)maximum is 256, therefore choose 300
	/*GIVEN SOURCE CODE*/
  	BigInteger();
  	BigInteger(const int&);
  	BigInteger(const std::string&);
  	BigInteger(const BigInteger&);
  	~BigInteger();

  	bool operator<(const BigInteger&) const;
  	const BigInteger operator%(const BigInteger&) const;
  	BigInteger& operator=(const BigInteger&);
  	bool iszero() const; //const is required, for gcd_by_euclid cannot be modified

  	friend std::ostream& operator<<(std::ostream&, const BigInteger&);

	/*EXTRA SOURCE CODE*/
	const BigInteger operator-(const BigInteger&) const; 
	bool operator==(const BigInteger&) const;
	void findlen();
	int a[digits];//a[] stands for biginteger array
	int length; //length is the amount of digits a[] stored

};


#endif