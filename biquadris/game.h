#ifndef _GAME_
#define _GAME_
#include "board.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "textDisplay.h"

class Game{
    std::unique_ptr<TextDisplay> td;
    //std::unique_ptr<GraphicalDisplay> gd;
    //Observer<State> observers;

    std::unique_ptr<Board> board1;
    std::unique_ptr<Board> board2;
    // player scores: 0 is player1, 1 is player2, 2 is hi
    std::vector<int> scores;
    // player levels: 0 is player1, 1 is player2
    std::vector<int> levels;
    bool textOnly;
    int seed;
    std::string scriptFile1;
    std::string scriptFile2;
    int startLevel;

    public:
    Game(bool textOnly, int seed, std::string scriptFile1, std::string scriptFile2, int startLevel);
    // sets scores
	void updateInfo();

    void setScores(int player, int score); // set score
    void play(); // play until game ends; returns winner name
    void reset();
};




#endif
