#define DEBUG

#include "game.h"
#include <memory>
#include <vector>

#include "textDisplay.h"
#include "graphicalDisplay.h"
#include <string>
#include "board.h"

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile1, string scriptFile2, int startLevel)
:td{new TextDisplay{}},gd{nullptr}, board1{nullptr},board2{nullptr}, textOnly{textOnly},
seed{seed}, scriptFile1{scriptFile1}, scriptFile2{scriptFile2}, startLevel{startLevel} {
#ifdef DEBUG
    cout << "Game ctor starts"<<endl;
#endif
	if (!textOnly){
		gd.reset( new GraphicalDisplay{});
	}
    
	board1.reset(new Board{1,td.get(), gd.get(), textOnly, seed, scriptFile1, startLevel});
	board2.reset(new Board{2,td.get(), gd.get(), textOnly, seed, scriptFile2, startLevel});
    board1->setOpponent(board2.get());
    board2->setOpponent(board1.get());
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
#ifdef DEBUG
    cout << "Game::updateInfo() score was " << scores.at(0)<<scores.at(1) << scores.at(2)<<endl;
#endif
	scores.at(0) += board1->getScore();

	scores.at(1) += board2->getScore();
#ifdef DEBUG
    cout << "Game::updateInfo() updates scores " << scores.at(0)<<scores.at(1) << scores.at(2)<<endl;
#endif
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
    if (!textOnly) {
        gd->updateScore(scores);
        gd->updateLevel(levels);
    }
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
    if (!textOnly) gd->display();

    while (true) {
        string gamestate = currplayer->play();
        if (gamestate == "restart!"){
            reset();
            currplayer = board2.get();
        } else if (gamestate == "lost!"){
            if (currplayer == board1.get()){
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
                cout << "Player 2 wins" << endl;
            } else {
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
				cout << "Player 1 wins" << endl;
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
#ifdef DEBUG
    cout << "Game::play() updates scores " << scores.at(0)<<scores.at(1) << scores.at(2)<<endl;
#endif
        td->print();
        if (!textOnly) gd->display();

    }
}

void Game::reset(){
#ifdef DEBUG
    cout << "Game reset starts"<<endl;
#endif

    td.reset(new TextDisplay);
    if(!textOnly)gd.reset(new GraphicalDisplay);
    board1.reset(new Board(1,td.get(), gd.get(), textOnly, seed, scriptFile1, startLevel));
    board2.reset(new Board(2,td.get(), gd.get(), textOnly, seed, scriptFile2, startLevel));
    scores[0] = 0;
    scores[1] = 0;
    levels[0] = startLevel;
    levels[1] = startLevel;
    td->print();
    if (!textOnly) gd->display();
#ifdef DEBUG
    cout << "Game::reset() updates scores " << scores.at(0)<<scores.at(1) << scores.at(2)<<endl;
#endif
}

