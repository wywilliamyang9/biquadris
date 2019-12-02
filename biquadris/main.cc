#include "game.h"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main(int argc, char *argv[]){
    argc = argc - 1;
    int seed = 0;
    bool textOnly = false;
    string scriptFile1 = "biquadris_sequence1.txt";
    string scriptFile2 = "biquadris_sequence2.txt";
    int startLevel = 0;
    for (int i = 1; i <= argc; i++){
        string tmparg = argv[i];
        if (tmparg == "-seed"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> seed)){
            }
            i++;
        } else if (tmparg == "-text"){
            textOnly = true;
        } else if (tmparg == "-scriptfile1"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> scriptFile1)){
            }
            i++;
        } else if (tmparg == "-scriptfile2"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> scriptFile2)){
            }
            i++;
        } else if (tmparg == "-startlevel"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> startLevel)){
            }
            i++;
        }
    }
    //std::unique_ptr<Game> game = make_unique<Game>(textOnly, seed, scriptFile1, scriptFile1, startLevel);
    unique_ptr<Game> game = make_unique<Game>(textOnly, seed, scriptFile1, scriptFile1, startLevel);
    game->play();
}
