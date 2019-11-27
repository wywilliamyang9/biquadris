#include "game.h"
#include <memory>
#include <vector>
#include <string>
#include "board.h"
#include "state.h"

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile1, string scriptFile2, int startLevel)
:textOnly{textOnly}, seed{seed}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2}, startLevel{startLevel}{
    td = new TextDisplay();
    attach(td);
    if (!textOnly){
        gd = new GraphicalDisplay();
        attach(gd);
    }
    board1 = new Board(1， td, gd, textOnly, seed, scriptFile1, startLevel);
    board2 = new Board(2，td, gd, textOnly, seed, scriptFile2, startLevel);
    board1->setOpponent(board2);
    board2->setOpponent(board1);
    for(int i = 0; i < 3; i++){
        score[i] = 0;
    }
    for(int i = 0; i < 2; i++){
        score[i] = startLevel;
    }
}

State Game::getInfo(){
    score[0] = board1->getScore();
    score[1] = board2->getScore();
    if (score[0] > score[2]){
        score[2] = score[0];
    } else if (score[1] > score[2]){
        score[2] = score[1];
    }
    levels[0] = board1->getLevel();
    levels[1] = board2->getLevel();
    return State{scores, levels};
}

string Game::play(){
    Player* currplayer = board1;
    while (true) {
        currplayer->play();
        if (currplayer = board1){
            currplayer = board2;
        } else {
            currplayer = board1;
        }
    }
}

