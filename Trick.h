#ifndef __TRICK_H__
#define __TRICK_H__

#include <iostream>
#include "CardPile.h"
#include "Player.h"

class Trick{
public:
	// plays single round consumes playerList, maxScore, currentHand
	void Play(vector<Player*>&, int, int);
};
#endif
