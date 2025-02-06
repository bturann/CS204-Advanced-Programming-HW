/******************************
	Author: Berkay Barýþ Turan
	Date: April 2021
******************************/
#include <iostream>
#include <sstream>
#include "bturan_Turan_BerkayBaris_hw5_Wallet.h"
using namespace std;

Wallet::Wallet()
//default constructor
{
	size_array = 0;
	dynamic_array = NULL;
}

Wallet::Wallet(int size)
//constructor
{
	size_array = size;
	dynamic_array = new Money[size_array];
}

Wallet::Wallet(const Wallet & copy)
//copy constructor
{
	createClone(copy);
}

void Wallet::createClone(const Wallet & copy)
//creates a deep copy of the parameter
{
	if(copy.size_array == 0)
	{
		size_array = 0;
		dynamic_array = NULL;
	}

	else
	{
		size_array = copy.size_array;

		dynamic_array = new Money[size_array];

		for(int i=0; i<copy.size_array;i++)
		{
			dynamic_array[i] =copy.dynamic_array[i];
		}
	}
}

int Wallet::return_Size() const
//return the size of the dynamic array of the wallet
{
	return size_array;
}

Money * Wallet::return_Array() const
//returns the head of the dynamic array of  the wallet
{
	return dynamic_array;
}

ostream & operator << (ostream & os,const Wallet & w)
{
	for(int i=0; i < w.return_Size(); i++)
	{
		os << w.return_Array()[i].currency << " " << w.return_Array()[i].amount;

		if((i+1) < w.return_Size())
			os << " - ";
	}
	os << endl;

	return os;
	
}

Wallet operator+ (const Wallet & lhs, const Money & rhs)
{
	if(lhs.return_Size() == 0)
	{

		Wallet new_wallet(1);
		new_wallet.return_Array()[0] = rhs;
		return new_wallet;
	}

	bool exist = false;

	Wallet lhs_copy(lhs);

	for(int i=0; i < lhs.return_Size(); i++)
	{
		if(lhs.return_Array()[i].currency == rhs.currency)
		{
			lhs_copy.return_Array()[i].amount = lhs.return_Array()[i].amount + rhs.amount;
			exist = true;
		}
	}

	if(exist)
	{
		Wallet new_wallet(lhs_copy.return_Size());

		for(int j=0; j < lhs_copy.return_Size(); j++)
		{
			new_wallet.return_Array()[j] = lhs_copy.return_Array()[j];
		}

		return new_wallet;
	}

	else
	{
		Wallet new_wallet(lhs.return_Size()+1);

		for(int j=0; j < lhs.return_Size(); j++)
		{
			new_wallet.return_Array()[j] = lhs.return_Array()[j];
		}
		
		new_wallet.return_Array()[lhs.return_Size()] = rhs;

		return new_wallet;
	}
}

Wallet operator + (const Wallet & lhs, const Wallet & rhs)
{
	int size_counter = lhs.return_Size() + rhs.return_Size();

	for(int i=0; i < rhs.return_Size(); i++)
	{
		for(int j=0; j < lhs.return_Size(); j++)
		{
			if(rhs.return_Array()[i].currency == lhs.return_Array()[j].currency)
				size_counter--;
		}
	}

	Wallet new_wallet(size_counter);

	for(int i=0; i < lhs.return_Size(); i++)
	{
		new_wallet.return_Array()[i] = lhs.return_Array()[i];
	}

	for(int j=0; j < rhs.return_Size(); j++)
	{
		int count_check = 0; //if count is smaller then the size of new_wallet, currency exists

		for(int a=0; a < new_wallet.return_Size(); a++)
		{
			if(rhs.return_Array()[j].currency == new_wallet.return_Array()[a].currency)
				new_wallet.return_Array()[a].amount += rhs.return_Array()[j].amount;

			else
				count_check++;
		}

		if(count_check == new_wallet.return_Size())
		{
			int i = 0;

			while(new_wallet.return_Array()[i].currency != "-")
			{
				i++;
			}

			new_wallet.return_Array()[i] = rhs.return_Array()[j];

		}
	}

	return new_wallet;
}

const Wallet & Wallet::operator =(const Wallet & rhs)
{

	if(this != &rhs)
	{
		size_array = rhs.size_array;
		dynamic_array = new Money[size_array];

		for(int i=0; i<size_array ;i++)
		{
			dynamic_array[i] = rhs.return_Array()[i];
		}
	}
	return *this;
}

const Wallet & Wallet::operator +=(const Wallet & rhs)
{
	Wallet temp(*this);
	temp = *this + rhs;
	
	Money * ptr;
	ptr = dynamic_array;

	size_array = temp.size_array;

	dynamic_array = new Money[size_array];

	for(int i=0; i<temp.size_array;i++)
	{
		dynamic_array[i] =temp.dynamic_array[i];
	}

	delete [] ptr;

	return *this;
}

bool Wallet::operator ==(const Wallet & rhs)
{
	if(size_array != rhs.size_array)
	{
		return false;
	}

	else
	{
		int count = 0; //the determine wheter all currencies are same

		for(int i=0; i<size_array; i++)
		{
			for(int j =0; j<rhs.size_array; j++)
			{
				if((dynamic_array[i].currency == rhs.dynamic_array[j].currency)&&(dynamic_array[i].amount == rhs.dynamic_array[j].amount))
					count++;
			}
		}

		if(count == size_array)
			return true;
		else
			return false;
	}
}

bool Wallet::operator >=(const Money & rhs)
{
	bool exist = false;
	int index;

	for(int i=0; i<size_array; i++)
	{
		if(dynamic_array[i].currency == rhs.currency)
		{
			index = i;
			exist = true;
		}
	}

	if(exist)
	{
		if(dynamic_array[index].amount >= rhs.amount)
			return true;

		else
			return false;
	}

	else
		return false;

}

Wallet operator -(const Wallet & lhs, const Money & rhs)
{
	bool exist = false;
	int index_found = 0;

	for(int i=0; i<lhs.return_Size(); i++)
	{
		if(lhs.return_Array()[i].currency == rhs.currency)
		{
			exist = true;
			index_found = i;
		}
	}

	if(exist)
	{
		Wallet lhs_copy(lhs);

		if(lhs_copy.return_Array()[index_found].amount < rhs.amount)
		{
			Wallet new_wallet(lhs_copy);
			return new_wallet;
		}

		else if(lhs_copy.return_Array()[index_found].amount == rhs.amount)
		{
			lhs_copy.return_Array()[index_found].amount -= rhs.amount;
			Wallet new_wallet(lhs_copy.return_Size()-1);

			int j = 0;

			for(int i=0; i<lhs_copy.return_Size(); i++)
			{
				if(lhs_copy.return_Array()[i].amount != 0)
				{
					new_wallet.return_Array()[j] = lhs_copy.return_Array()[i];
					j++;
				}
			}

			return new_wallet;

		}

		else if(lhs_copy.return_Array()[index_found].amount > rhs.amount)
		{
			lhs_copy.return_Array()[index_found].amount -= rhs.amount;
			Wallet new_wallet(lhs_copy);
			return new_wallet;
		}

	}

	else
	{
		Wallet new_wallet(lhs);
		return new_wallet;
	}



}

bool operator <=(const Money &lhs, const Wallet & rhs)
{
	Wallet temp_wallet(rhs);
	Money temp_money(lhs.currency,lhs.amount);

	if(temp_wallet >= temp_money)
		return true;

	else
		return false;
}

Wallet::~Wallet()
//destructor
{
	delete [] dynamic_array;
}


