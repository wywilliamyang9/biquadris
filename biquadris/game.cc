#define DEBUG

#include "game.h"
#include <memory>
#include <vector>
#include <string>
#include "board.h"

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile1, string scriptFile2, int startLevel)
:textOnly{textOnly}, seed{seed}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2}, startLevel{startLevel},
td{ new TextDisplay{} } {
#ifdef DEBUG
    cout << "Game ctor starts"<<endl;
#endif
	//td = make_unique(new TextDisplay());
	//attach(&(*td));
	/*if (!textOnly){
		gd = new GraphicalDisplay();
		attach(gd);
	}*/
    
	board1.reset(new Board{ 1,td.get(), /*gd,*/ textOnly, seed, scriptFile1, startLevel });
	board2.reset(new Board{2,td.get(), /*gd,*/ textOnly, seed, scriptFile2, startLevel});
    board1->setOpponent(&*board2);
    board2->setOpponent(&*board1);
    for(int i = 0; i < 3; i++){
		scores.emplace_back(0);
    }
    for(int i = 0; i < 2; i++){
		levels.emplace_back(0);
	}
#ifdef DEBUG
    cout << "Game ctor ends"<<endl;
#endif
}

void Game::updateInfo() {
#ifdef DEBUG
    cout << "Game::updateInfo() starts"<<endl;
#endif
	scores.at(0) = board1->getScore();

	scores.at(1) = board2->getScore();
	if (scores[0] > scores[2]) {
		scores[2] = scores[0];
	}
	else if (scores[1] > scores[2]) {
		scores[2] = scores[1];
	}
	levels[0] = board1->getLevel();
	levels[1] = board2->getLevel();
    td->updateScore(scores);
    td->updateLevel(levels);
#ifdef DEBUG
    cout << "Game::updateInfo() ends"<<endl;
#endif
}

void Game::play(){
#ifdef DEBUG
    cout << "Game::play() starts"<<endl;
#endif
    Board* currplayer = board1.get();
    updateInfo();
    td->print();

    while (true) {
        string gamestate = currplayer->play();
        if (gamestate == "restart!"){
            currplayer = board1.get();
            reset();
        } else if (gamestate == "lost!"){
            if (currplayer == board1.get()){
                cout << "Player 2 wins";
            } else {
				cout << "Player 1 wins";
            }
            reset();
        } else if (gamestate == "eof!"){
            break;
        }
        if (currplayer == board1.get()){
            currplayer = board2.get();
        } else {
            currplayer = board1.get();
        }
        updateInfo();
        td->print();
    }
}

void Game::reset(){
    board1.reset(new Board(1,td.get(), /*gd,*/ textOnly, seed, scriptFile1, startLevel));
    board2.reset(new Board(2,td.get(), /*gd,*/ textOnly, seed, scriptFile2, startLevel));
    scores[0] = 0;
    scores[1] = 0;
    levels[0] = startLevel;
    levels[1] = startLevel;
    td->print();
}


