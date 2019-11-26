#ifndef _GAME_
#define _GAME_
#include "board.h"
#include <String>
#include <iostream>
#include "subject.h"
#include "observer.h"
#include <memory>

class Game : public subject <vector<int>> {
    std::unique_ptr<TextDisplay> td = nullptr;
    std::unique_ptr<GraphicalDisplay> gd = nullptr;
    Observer observers;

    std::unique_ptr<Board> board1;
    std::unique_ptr<Board> board2;
    // player scores: 0 is player1, 1 is player2, 2 is hi
    std::vector<int> scores;
    bool textOnly;
    int seed;
    std::string scriptFile1;
    std::string scriptFile2;
    int startLevel;

    public:
    Game(bool textOnly, int seed, string scriptFile1, string scriptFile2, int startLevel);
    // sets scores
    vector<int> getinfo() const override;
    void setScores(int player, int score); // set score
    std::string Play(); // play until game ends; returns winner name
};




#endif
