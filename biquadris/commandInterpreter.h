#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_
#include <map>
#include "commands.h"
#include <String>
class CommandInterpreter {
    std::map<string, Commands> cmdDictionary
    public:
    CommandInterpreter();

    bool checkCMD(std::string); // returns true if is a valid cmd
    Command interpretCMD(std::string);
    void addNewCMD(std::String,Command);
    void removeCMD(std::String);
    
}

#endif
