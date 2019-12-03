#include "commandInterpreter.h"
using namespace std;

CommandInterpreter::CommandInterpreter() {
    cmdDictionary["lef"] = Command::Left;
    cmdDictionary["left"] = Command::Left;
    cmdDictionary["ri"] = Command::Right;
    cmdDictionary["rig"] = Command::Right;
    cmdDictionary["righ"] = Command::Right;
    cmdDictionary["right"] = Command::Right;
    cmdDictionary["do"] = Command::Down;
    cmdDictionary["dow"] = Command::Down;
    cmdDictionary["down"] = Command::Down;
    cmdDictionary["cl"] = Command::ClockWise;
    cmdDictionary["clo"] = Command::ClockWise;
    cmdDictionary["cloc"] = Command::ClockWise;
    cmdDictionary["clock"] = Command::ClockWise;
    cmdDictionary["clockw"] = Command::ClockWise;
    cmdDictionary["clockwi"] = Command::ClockWise;
    cmdDictionary["clockwis"] = Command::ClockWise;
    cmdDictionary["clockwise"] = Command::ClockWise;
    cmdDictionary["co"] = Command::CounterClockWise;
    cmdDictionary["cou"] = Command::CounterClockWise;
    cmdDictionary["coun"] = Command::CounterClockWise;
    cmdDictionary["count"] = Command::CounterClockWise;
    cmdDictionary["counte"] = Command::CounterClockWise;
    cmdDictionary["counter"] = Command::CounterClockWise;
    cmdDictionary["counterc"] = Command::CounterClockWise;
    cmdDictionary["countercl"] = Command::CounterClockWise;
    cmdDictionary["counterclo"] = Command::CounterClockWise;
    cmdDictionary["countercloc"] = Command::CounterClockWise;
    cmdDictionary["counterclock"] = Command::CounterClockWise;
    cmdDictionary["counterclockw"] = Command::CounterClockWise;
    cmdDictionary["counterclockwi"] = Command::CounterClockWise;
    cmdDictionary["counterclockwis"] = Command::CounterClockWise;
    cmdDictionary["counterclockwise"] = Command::CounterClockWise;

    cmdDictionary["dr"] = Command::Drop;
    cmdDictionary["dro"] = Command::Drop;
    cmdDictionary["drop"] = Command::Drop;
    
    cmdDictionary["levelu"] = Command::LevelUp;
    cmdDictionary["levelup"] = Command::LevelUp;
    cmdDictionary["leveld"] = Command::LevelDown;
    cmdDictionary["leveldo"] = Command::LevelDown;
    cmdDictionary["leveldow"] = Command::LevelDown;
    cmdDictionary["leveldown"] = Command::LevelDown;

    
    cmdDictionary["n"] = Command::NoRandom;
    cmdDictionary["no"] = Command::NoRandom;
    cmdDictionary["nor"] = Command::NoRandom;
    cmdDictionary["nora"] = Command::NoRandom;
    cmdDictionary["noran"] = Command::NoRandom;
    cmdDictionary["norand"] = Command::NoRandom;
    cmdDictionary["norando"] = Command::NoRandom;
    cmdDictionary["norandom"] = Command::NoRandom;

    cmdDictionary["ra"] = Command::Random;
    cmdDictionary["ran"] = Command::Random;
    cmdDictionary["rand"] = Command::Random;
    cmdDictionary["rando"] = Command::Random;
    cmdDictionary["random"] = Command::Random;

    cmdDictionary["se"] = Command::Sequence;
    cmdDictionary["seq"] = Command::Sequence;
    cmdDictionary["sequ"] = Command::Sequence;
    cmdDictionary["seque"] = Command::Sequence;
    cmdDictionary["sequen"] = Command::Sequence;
    cmdDictionary["sequenc"] = Command::Sequence;
    cmdDictionary["sequence"] = Command::Sequence;

    cmdDictionary["I"] = Command::I;
    cmdDictionary["i"] = Command::I;
    cmdDictionary["J"] = Command::J;
    cmdDictionary["j"] = Command::J;
    cmdDictionary["L"] = Command::L;
    cmdDictionary["l"] = Command::L;
    cmdDictionary["O"] = Command::O;
    cmdDictionary["o"] = Command::O;
    cmdDictionary["S"] = Command::S;
    cmdDictionary["s"] = Command::S;
    cmdDictionary["Z"] = Command::Z;
    cmdDictionary["z"] = Command::Z;
    cmdDictionary["T"] = Command::T;
    cmdDictionary["t"] = Command::T;

    cmdDictionary["re"] = Command::Restart;
    cmdDictionary["res"] = Command::Restart;
    cmdDictionary["rest"] = Command::Restart;
    cmdDictionary["resta"] = Command::Restart;
    cmdDictionary["restar"] = Command::Restart;
    cmdDictionary["restart"] = Command::Restart;

    cmdDictionary["b"] = Command::Blind;
    cmdDictionary["bl"] = Command::Blind;
    cmdDictionary["bli"] = Command::Blind;
    cmdDictionary["blin"] = Command::Blind;
    cmdDictionary["blind"] = Command::Blind;

    cmdDictionary["h"] = Command::Heavy;
    cmdDictionary["he"] = Command::Heavy;
    cmdDictionary["hea"] = Command::Heavy;
    cmdDictionary["heav"] = Command::Heavy;
    cmdDictionary["heavy"] = Command::Heavy;

    cmdDictionary["f"] = Command::Force;
    cmdDictionary["fo"] = Command::Force;
    cmdDictionary["for"] = Command::Force;
    cmdDictionary["forc"] = Command::Force;
    cmdDictionary["force"] = Command::Force;

    cmdDictionary["ho"] = Command::Hold;
    cmdDictionary["hol"] = Command::Hold;
    cmdDictionary["hold"] = Command::Hold;

    cmdDictionary["sh"] = Command::Shuffle;
    cmdDictionary["shu"] = Command::Shuffle;
    cmdDictionary["shuf"] = Command::Shuffle;
    cmdDictionary["shuff"] = Command::Shuffle;
    cmdDictionary["shuffl"] = Command::Shuffle;
    cmdDictionary["shuffle"] = Command::Shuffle;
}

void CommandInterpreter::addNewCMD(string s,Command cmd){
    cmdDictionary[s] = cmd;
}

void CommandInterpreter::removeCMD(string s){
    cmdDictionary.erase(s);
}
bool CommandInterpreter::checkCMD(std::string s){return cmdDictionary.count(s); } // returns true if is a valid cmd
Command CommandInterpreter::interpretCMD(std::string s){return cmdDictionary[s];}

