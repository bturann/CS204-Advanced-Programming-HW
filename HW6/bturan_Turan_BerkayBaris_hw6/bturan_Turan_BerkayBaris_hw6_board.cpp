#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bturan_Turan_BerkayBaris_hw6_board.h"
using namespace std;

template <class type>
Board<type>::Board(int row_num, int col_num)
//parametric constructor
{
	rows = row_num;
	cols = col_num;

	matrix = new Card<type>*[rows];

	for(int i=0; i<rows; i++)
		matrix[i] = new Card<type>[cols];

}

template <class type>
Board<type>::Board(const Board<type> & copy)
//deep copy constructor
{
	rows = copy.rows;
	cols = copy.cols;

	matrix = new Card<type>*[rows];

	for(int i=0; i<cols; i++)
		matrix[i] = new Card<type>[cols];

	for(int i=0; i<cols; i++)
		for(int j=0; j<cols; j++)
		{
			matrix[i][j].value = copy.matrix[i][j].value;
			matrix[i][j].status = copy.matrix[i][j].status;
		}
}

template <class type>
Board<type>::~Board()
//destructor
{
	for(int i=0; i<rows; i++)
		delete [] matrix[i];
	delete [] matrix;

	matrix = NULL;

}

template <class type>
void Board<type>::readBoardFromFile(ifstream & is)
{
	string line = "";
	type current_instance;

	for(int i=0; i<rows; i++)
	{
		getline(is,line);
		istringstream s(line);
		for(int j=0; j<cols; j++)
		{
			s >> current_instance;
			matrix[i][j].value = current_instance;
		}
	}
}

template <class type>
void Board<type>::displayBoard() const
//displays the current board
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(matrix[i][j].status == true)
				cout << "X" << " ";
			else
				cout << matrix[i][j].value << " ";
		}
		cout << endl;
	}
}
template <class type>
void Board<type>::closeCard(int row_n, int column_n)
//changes the status of the card to true (closed)
{
	matrix[row_n][column_n].status = true;
}

template <class type>
int Board<type>::getRow() const
//returns the row number of the matrix
{
	return rows;
}

template <class type>
int Board<type>::getColumn() const
//return the columns number of the matrix
{
	return cols;
}

template <class type>
Card<type> ** Board<type>::getMatrix() const
//return the pointer pointer of matrix
{
	return matrix;
}

template <class type>
void Board<type>::changeStatus(int row, int column)
//changes the status of the card tot true
{
	matrix[row][column].status = false;
}