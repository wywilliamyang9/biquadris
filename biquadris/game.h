#ifndef _GAME_
#define _GAME_
#include "board.h"
#include <String>
#include <iostream>
#include "subject.h"
#include "observer.h"

class Game : public subject <vector<int>> {
    Observer observers;

    Board board1;
    Board board2;
    // player scores: 0 is player1, 1 is player2, 2 is hi
    vector<int> scores;

    public:
    // sets scores
    vector<int> getinfo() const override;
    void setScores(vector<int>); // set player1's score
    String Play(); // play until game ends; returns winner name
};




#endif
