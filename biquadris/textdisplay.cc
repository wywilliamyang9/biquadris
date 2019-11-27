#include "textdisplay.h"
#include "info.h"
#include "colour.h"
#include <vector>

using namespace std;

char convertColour(Colour colour){
    if (colour == Colour::Red){
        return 'Z';
    } else if (colour == Colour::Orange){
        return 'L';
    } else if (colour == Colour::LightBlue){
        return 'I';
    } else if (colour == Colour::Blue){
        return 'J';
    } else if (colour == Colour::Yellow){
        return 'O';
    } else if (colour == Colour::Green){
        return 'S';
    } else if (colour == Colour::Purple){
        return 'T';
    } else if (colour == Colour::White){
        return ' ';
    }
}

TextDisplay::TextDisplay(){
    theDisplay.clear();
    for (int i = 0; i < gridHeight; ++i){
        vector<char> temp1;
        vector<char> temp2;
        for (int j = 0; j < gridWidth; ++j){
            temp1.emplace_back(' ');
            temp2.emplace_back(' ');
        }
        board1.emplace_back(temp);
        board2.emplace_back(temp);
    }
}

void TextDisplay::notify(Subject<Info> &whoNotified) override{
    Info currinfo{whoNotified.getInfo()};
    if (currinfo.boardnum == 1){
        if (currinfo.blinded){
            board1[currinfo.coord.row][currinfo.coord.col] = '?';
        } else {
            board1[currinfo.coord.row][currinfo.coord.col] = convertColour(currinfo.colour);
        }
    } else if (currinfo.boardnum == 2){
        if (currinfo.blinded){
            board2[currinfo.coord.row][currinfo.coord.col] = '?';
        } else {
            board2[currinfo.coord.row][currinfo.coord.col] = convertColour(currinfo.colour);
        }
    }
}

void TextDisplay::notify(Subject<State> &whoNotified) override{
    vector<int> currinfo{whoNotified.getInfo()};
    scores[0] = currinfo.scores[0];
    scores[1] = currinfo.scores[1];
    scores[2] = currinfo.scores[2];
    levels[0] = currinfo.levels[0];
    levels[1] = currinfo.levels[1];
}

void TextDisplay::notify(Subject<NextBlock> &whoNotified) override{
    vector<int> currinfo{whoNotified.getInfo()};
    scores[0] = currinfo.scores[0];
    scores[1] = currinfo.scores[1];
    scores[2] = currinfo.scores[2];
    levels[0] = currinfo.levels[0];
    levels[1] = currinfo.levels[1];
}

void TextView::print() {
	printLevel();
    printHighScore();
	printScore();
	cout << "-----------   -----------" << endl;
	printBoards();
	cout << "-----------   -----------" << endl;
	printNext();
}

void TextView::printLevel() {
	cout << "LEVEL: " << levels[0];
	cout << "    ";
    cout << "LEVEL: " << levels[1] << endl;
}

void TextView::printHighScore() {
	cout << "HISCORE: " << scores[3];
	cout << "  ";
	cout << "HISCORE: " << scores[3] << endl;
}

void TextView::printScore() {
	cout << "SCORE: " << scores[0];
	cout << "    ";
	cout << "SCORE: " << scores[1] << endl;
}

void TextView::printBoards() {
	for (int i = 15; i >= 0; i--) {
		for (int j = 0; j < 23; j++) {
			if (j < 11) {
				cout << board1[i][j];
			}
			else if (j == 11) {
				cout << " ";
			}
			else {
				cout << board2[i][j-11];
			}
		}
		cout << endl;
	
	}
	
}
void TextView::printNext() {
	cout << "Next:       Next:" << endl;
	cout << model->getBoardOne()->getNextType();
	cout << "             " << model->getBoardTwo()->getNextType() << endl;
}
