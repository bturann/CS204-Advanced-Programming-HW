#ifndef _BTURAN_TURAN_BERKAYBARIS_HW6_PLAYER_H
#define _BTURAN_TURAN_BERKAYBARIS_HW6_PLAYER_H

#include <iostream>
#include <string>
#include "bturan_Turan_BerkayBaris_hw6_board.h"

using namespace std;

template <class type>
class Player
{
public:
	Player(Board<type> &);
	type openCard(int, int);
	bool validMove(int, int);
	void increaseNumberOfSuccess();
	int getNumberOfSuccess();

private:
	Board<type> & board;
	int score;
};

#include "bturan_Turan_BerkayBaris_hw6_player.cpp"

#endif