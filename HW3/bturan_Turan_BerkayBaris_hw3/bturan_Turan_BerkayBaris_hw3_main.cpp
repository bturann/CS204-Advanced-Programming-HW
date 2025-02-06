/*********************************
	Author: Berkay Baris Turan
	Date: 30.03.2021
*********************************/

#include <iostream>
#include <string>
#include <sstream> //for istringstream
#include "SubSeqsList.h"
using namespace std;

/* Begin: code taken from bturan_Turan_BerkayBaris_hw2.cpp and updated */
bool isEmpty(string numbers)
//returns true if there is no number in numbers
//returns false if there is any number
{
	if(numbers.empty())
		return true;
	else
	{
		for(int i=0; i< numbers.length(); i++)
		{
			if(numbers[i] != ' ' && numbers[i] != '\t')
				return false;
		}
		return true;
	}
}
/* End: code taken from bturan_Turan_BerkayBaris_hw2.cpp and updated */

int main()
{
	string numbers;

	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);

	cout << endl;

	if(isEmpty(numbers))
		cout << "FINAL CONTENT" << endl << "List is empty!" << endl;
	else
	{
		SubSeqsList list;
;
		
		int current_number;
		istringstream input(numbers);

		while(input >> current_number)
		{
			if(current_number >= 0)
			{
				if(!list.Exists(current_number))
				{
					SubSeqNode * ptr_newnode = new SubSeqNode(current_number,NULL);
					list.Insert(ptr_newnode);
				}	
				else
				{
					cout << current_number <<" is already in the list!" << endl;
				}
			}
			else
			{
				if(list.Exists(abs(current_number)))
				{

					while(list.Found_In_Sequence(abs(current_number)) != NULL)
					{
						list.Delete(list.Found_In_Sequence(abs(current_number)));

					}

					cout << "All subsequence(s) containing " << abs(current_number) << " has/have been deleted" << endl;

				}
				else
				{
					cout << "There is no subsequence that contains " << abs(current_number) << " to be deleted" << endl;
				}
			}
		}


		list.Display();

		list.DeleteEntire();

	}
		
	return 0;
}