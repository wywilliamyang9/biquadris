#include "game.h"



Game(bool textOnly, int seed, string scriptFile1, string scriptFile2, int startLevel);
// sets scores
vector<int> getinfo() const override;
void setScores(int player, int score); // set player1's score
string Play();