//#define DEBUG

#include "graphicalDisplay.h"
#include "info.h"
#include <iostream>
#include "colour.h"
#include <vector>
#include "board.h"
using namespace std;

GraphicalDisplay::GraphicalDisplay(){
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
	}
}

void GraphicalDisplay::notify(Subject &whoNotified) {
#ifdef DEBUG
    cout << "GraphicalDisplay::notify() starts"<<endl;
#endif
    // if called upon a row clear, return.
    if (caller.getCleared()) return;
    
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

void GraphicalDisplay::updateNextBlock(NextBlock nextBlockInfo){
    if (nextBlockInfo.boardnum == 1){
        nextblock[0] = convertColour(nextBlockInfo.colour);
    } else if (nextBlockInfo.boardnum == 2){
        nextblock[1] = convertColour(nextBlockInfo.colour);
    }
}

void GraphicalDisplay::updateScore(vector<int> newScores){
    scores[0] = newScores[0];
    scores[1] = newScores[1];
    scores[2] = newScores[2];
}

void GraphicalDisplay::updateLevel(vector<int> newLevels){
    levels[0] = newLevels[0];
    levels[1] = newLevels[1];
}

void GraphicalDisplay::updateLevel(int newLevel, int boardnum){
    if (boardnum == 1){
        levels[0] = newLevel;
    } else if (boardnum) {
        levels[1] = newLevel;
    }
}


void GraphicalDisplay::display() {
#ifdef DEBUG
    cout << "GraphicalDisplay::display() starts"<<endl;
#endif
	displayLevel();
    displayHighScore();
	displayScore();
	cout << "-----------   -----------" << endl;
	displayBoards();
	cout << "-----------   -----------" << endl;
	displayNextBlock();
    
#ifdef DEBUG
    cout << "GraphicalDisplay::display() ends"<<endl;
#endif
}

void GraphicalDisplay::displayLevel() {
	cout << "LEVEL: " << levels[0];
	cout << "      ";
    cout << "LEVEL: " << levels[1] << endl;
}

void GraphicalDisplay::displayHighScore() {
	cout << "HISCORE: " << scores[3];
	cout << "    ";
	cout << "HISCORE: " << scores[3] << endl;
}

void GraphicalDisplay::displayScore() {
	cout << "SCORE: " << scores[0];
	cout << "      ";
	cout << "SCORE: " << scores[1] << endl;
}

void GraphicalDisplay::displayBoards() {
	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j <= 25; j++) {
			if (j < gridWidth) {
				cout << board1[i][j];
			} else if (j < 14) {
				cout << " ";
			} else {
				cout << board2[i][j-3-gridWidth];
			}
		}
		cout << endl;
	
	}	
}

string displayBlock(char type, int line){
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

void GraphicalDisplay::displayNextBlock() {
	cout << "Next:         Next:" << endl;
    cout << displayBlock(nextblock[0], 1) << "          " << displayBlock(nextblock[1], 1) << endl;
    cout << displayBlock(nextblock[0], 2) << "          " << displayBlock(nextblock[1], 2) << endl;
}
