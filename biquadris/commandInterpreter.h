#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_
#include <map>
#include "commands.h"
#include <String>
class CommandInterpreter {
    std::map<string, Commands> cmdDictionary
    public:
    CommandInterpreter();
    void addNewCMD(String,Command);
    void removeCMD(String, Command);
}

#endif
