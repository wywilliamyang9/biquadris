//#define DEBUG
//#define DEBUG2
#include "textDisplay.h"
#include "info.h"
#include <iostream>
#include "colour.h"
#include <vector>
using namespace std;

TextDisplay::TextDisplay(bool printheld): printheld{printheld}{
    //theDisplay.clear();
    for (int i = 0; i < gridHeight; ++i){
        vector<char> temp1;
        vector<char> temp2;
        for (int j = 0; j < gridWidth; ++j){
            temp1.emplace_back(' ');
            temp2.emplace_back(' ');
        }
        
        board1.emplace_back(temp1);
        board2.emplace_back(temp2);
    }
    for(int i = 0; i < 3; i++){
		scores.emplace_back(0);
    }
    for(int i = 0; i < 2; i++){
		levels.emplace_back(0);
        nextblock.emplace_back('A');
        heldblock.emplace_back('A');
	}
}

void TextDisplay::notify(Subject &whoNotified) {
    // if called upon a row clear, return.
    if (whoNotified.getCleared()) return;
#ifdef DEBUG
    cout << "TextDisplay::notify() notified!"<<endl;
#endif
    Info currinfo{whoNotified.getinfo()};
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

void TextDisplay::updateHeldBlock(NextBlock heldBlockInfo){
    #ifdef DEBUG
    cout << "TextDisplay::updateHeldBlock"<<endl;
#endif
    if (heldBlockInfo.boardnum == 1){
        heldblock[0] = convertColour(heldBlockInfo.colour);
    } else if (heldBlockInfo.boardnum == 2){
        heldblock[1] = convertColour(heldBlockInfo.colour);
    }
}

void TextDisplay::updateNextBlock(NextBlock nextBlockInfo){
    if (nextBlockInfo.boardnum == 1){
        nextblock[0] = convertColour(nextBlockInfo.colour);
    } else if (nextBlockInfo.boardnum == 2){
        nextblock[1] = convertColour(nextBlockInfo.colour);
    }
}

void TextDisplay::updateScore(vector<int> newScores){
#ifdef DEBUG
    cout << "TextDisplay::updateScore() starts!"<<endl;
#endif
#ifdef DEBUG
    cout << "TextDisplay::updateScore() new scores sizse is : "<<newScores.size()<<endl;
    cout << "They are " << newScore.at(0) << newScore.at(1) << newScore.at(2) << endl;
#endif
    scores[0] = newScores[0];
    scores[1] = newScores[1];
    scores[2] = newScores[2];
}

void TextDisplay::updateScore(int newScore, int boardnum){
    if (boardnum == 1){
        scores[0] = newScore;
    } else if (boardnum) {
        scores[1] = newScore;
    }
    if (newScore > scores[2]){
        scores[2] = newScore;
    }
}


void TextDisplay::updateLevel(vector<int> newLevels){
    levels[0] = newLevels[0];
    levels[1] = newLevels[1];
}

void TextDisplay::updateLevel(int newLevel, int boardnum){
    if (boardnum == 1){
        levels[0] = newLevel;
    } else if (boardnum) {
        levels[1] = newLevel;
    }
}


void TextDisplay::print() {
#ifdef DEBUG
    cout << "TextDisplay::print() starts"<<endl;
#endif
	printLevel();
    printHighScore();
	printScore();
	cout << "-----------   -----------" << endl;
	printBoards();
	cout << "-----------   -----------" << endl;
	printNextBlock();
    if (printheld){
        printHeldBlock();
    }
#ifdef DEBUG
    cout << "TextDisplay::print() ends"<<endl;
#endif
}

void TextDisplay::printLevel() {
	cout << "LEVEL: " << levels[0];
	cout << "      ";
    cout << "LEVEL: " << levels[1] << endl;
}

void TextDisplay::printHighScore() {
#ifdef DEBUG
    cout << "TextDisplay::printHighScore() starts!"<<endl;
#endif
	cout << "HISCORE: " << scores[2];
	cout << "    ";
	cout << "HISCORE: " << scores[2] << endl;
}

void TextDisplay::printScore() {
	cout << "SCORE: " << scores[0];
	cout << "      ";
	cout << "SCORE: " << scores[1] << endl;
}

void TextDisplay::printBoards() {
	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j < 25; j++) {
			if (j < gridWidth) {
				cout << board1.at(i).at(j);
			} else if (j < 14) {
				cout << " ";
			} else {
				cout << board2.at(i).at(j-3-gridWidth);
			}
		}
		cout << endl;
	
	}	
}

string TextDisplay::printBlock(char type, int line){
    if (type == 'J' && line == 1){
        return "J   ";
    } else if (type == 'J' && line == 2){
        return "JJJ ";
    } else if (type == 'I' && line == 1){
        return "    ";
    } else if (type == 'I' && line == 2){
        return "IIII";
    } else if (type == 'L' && line == 1){
        return "  L ";
    } else if (type == 'L' && line == 2){
        return "LLL ";
    } else if (type == 'O' && line == 1){
        return "OO  ";
    } else if (type == 'O' && line == 2){
        return "OO  ";
    } else if (type == 'S' && line == 1){
        return " SS ";
    } else if (type == 'S' && line == 2){
        return "SS  ";
    } else if (type == 'Z' && line == 1){
        return "ZZ  ";
    } else if (type == 'Z' && line == 2){
        return " ZZ ";
    } else if (type == 'T' && line == 1){
        return "TTT ";
    } else if (type == 'T' && line == 2){
        return " T  ";
    }
	return "";
}

void TextDisplay::printNextBlock() {
	cout << "Next:         Next:" << endl;
    cout << printBlock(nextblock[0], 1) << "          " << printBlock(nextblock[1], 1) << endl;
    cout << printBlock(nextblock[0], 2) << "          " << printBlock(nextblock[1], 2) << endl;
}

void TextDisplay::printHeldBlock() {
	cout << "Held:         Held:" << endl;
    cout << printBlock(heldblock[0], 1) << "          " << printBlock(heldblock[1], 1) << endl;
    cout << printBlock(heldblock[0], 2) << "          " << printBlock(heldblock[1], 2) << endl;
}

