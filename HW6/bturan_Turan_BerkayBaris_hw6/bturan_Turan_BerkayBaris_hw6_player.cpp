#include <iostream>
#include <string>
#include "bturan_Turan_BerkayBaris_hw6_player.h"
#include "bturan_Turan_BerkayBaris_hw6_board.h"
using namespace std;

template <class type>
Player<type>::Player(Board<type> & brd)
//parametric constructor
	: board(brd), score(int(0))
{}

template <class type>
type Player<type>::openCard(int row, int column) //return type temp type
//retuns the value of the [row][column]'th card on the board
{
	type value = board.getMatrix()[row][column].value;
	board.changeStatus(row,column);
	return value;
}

template <class type>
bool Player<type>::validMove(int row, int column)
//if a valid move return true, else false
{
	if((board.getColumn() <= column) || (board.getRow() <= row))
		return false;

	else if(board.getMatrix()[row][column].status == false)
		return false;

	return true;
}

template <class type>
void Player<type>::increaseNumberOfSuccess()
//increments score of the player by one
{
	score++;
}

template <class type>
int Player<type>::getNumberOfSuccess()
//returns score of the player
{
	return score;
}