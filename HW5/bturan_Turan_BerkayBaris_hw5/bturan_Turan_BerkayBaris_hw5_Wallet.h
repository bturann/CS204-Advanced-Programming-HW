/******************************
	Author: Berkay Barýþ Turan
	Date: April 2021
******************************/

#ifndef _BTURAN_TURAN_BERKAYBARIS_HW5_WALLET_H
#define _BTURAN_TURAN_BERKAYBARIS_HW5_WALLET_H

#include <iostream>
#include <string>
using namespace std;

struct Money
{
	string currency;
	double amount;

	Money::Money() :
		currency("-"), amount(0.0)
	{}

	Money::Money(string name, double num)
		: currency(name), amount(num)
	{}
};

class Wallet
{
public:
	Wallet(); //default constructor
	Wallet(int);//constructor
	Wallet(const Wallet &); //deep copy constructor
	~Wallet(); //destructor
	void createClone(const Wallet &); //creates a deep copy of the parameter
	int return_Size() const; //returns the size of wallet's array
	Money * return_Array() const; //returns the head of wallet's array
	const Wallet & Wallet::operator =(const Wallet &);
	const Wallet & Wallet::operator +=(const Wallet &);
	bool Wallet::operator ==(const Wallet &);
	bool Wallet::operator >=(const Money &);

private:
	int size_array;
	Money *dynamic_array;
};

//free functions

ostream & operator << (ostream &, const Wallet &);
Wallet operator + (const Wallet &, const Money &);
Wallet operator + (const Wallet &, const Wallet &);
Wallet operator - (const Wallet &, const Money &);
bool operator <=(const Money &, const Wallet &);

#endif