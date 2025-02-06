#ifndef _BTURAN_TURAN_BERKAYBARIS_HW6_BOARD_H
#define _BTURAN_TURAN_BERKAYBARIS_HW6_BOARD_H

#include <iostream>
#include <string>
using namespace std;

template <class type>
struct Card //temp (int)
{
//if status is true, card is closed
//if status is false, card is opened

	type value; //change int
	bool status;

	Card<type>()
		:status(true)
	{}

};

template <class type>
class Board
{
public:
	Board(int,int); 
	Board(const Board &);
	~Board();
	void readBoardFromFile(ifstream &);
	void displayBoard() const;
	void closeCard(int, int);
	int getRow() const;
	int getColumn() const;
	Card<type> **getMatrix() const;
	void changeStatus(int, int);

private:
	Card<type> **matrix; //pointer of dynamic martix //temp (int)!
	int rows;
	int cols;
};

#include "bturan_Turan_BerkayBaris_hw6_board.cpp"

#endif