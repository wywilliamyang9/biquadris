#ifndef _GAME_
#define _GAME_
#include "board.h"
#include <String>
#include <iostream>

class Game {
    Board board1;
    Board board2;
    int score1;
    int score2;
    int hi;
    public:
    void setScore1(Integer); // set player1's score
    void setScore2(Integer); // set player2's score
    void setHiScore(Integer); // set highest score
    String Play(); // play until game ends; returns winner name
};




#endif
