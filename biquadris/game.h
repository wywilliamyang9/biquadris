#ifndef _GAME_
#define _GAME_
#include "board.h"
#include <string>
#include <vector>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include <memory>
#include "state.h"
#include "textDisplay.h"

class Game : public Subject <State> {
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
    State getinfo() const override;
	void updateInfo();

    void setScores(int player, int score); // set score
    std::string play(); // play until game ends; returns winner name
    void reset();
};

#endif
