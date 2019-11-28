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
    /*if (!textOnly){
        gd = new GraphicalDisplay();
        attach(gd);
    }*/
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

State Game::getInfo() const{
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

void Game::play(){
    Player* currplayer = board1;
    while (true) {
        string gamestate = currplayer->play();
        if (gamestate == "restart!"){
            currplayer = board1;
            reset();
        } else if (gamestate == "lost!"){
            if (currplayer = board1){
                cout << "Player 2 wins";
            } else {
                cout << "Player 1 wins"
            }
        } else if (gamestate == "eof!"){
            break;
        }
        if (currplayer = board1){
            currplayer = board2;
        } else {
            currplayer = board1;
        }
    }
}

void Game::reset(){
    board1.reset(new Board(1， td, gd, textOnly, seed, scriptFile1, startLevel));
    board2.reset(new Board(2，td, gd, textOnly, seed, scriptFile2, startLevel));
    scores[0] = 0;
    scores[1] = 0;
    levels[0] = startLevel;
    levels[1] = startLevel;
}
