#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_
#include <map>
#include "commands.h"
#include <String>
class CommandInterpreter {
    std::map<string, Commands> cmdDictionary
    public:
    CommandInterpreter();
    void addNewCMD(std::String,Command);
    void removeCMD(std::String);
}

#endif
