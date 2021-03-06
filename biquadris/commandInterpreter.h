#ifndef _COMMANDINTERPRETER_
#define _COMMANDINTERPRETER_
#include <map>
#include "command.h"
#include <string>

class CommandInterpreter {
    std::map<std::string, Command> cmdDictionary;
    public:
    CommandInterpreter();

    bool checkCMD(std::string); // returns true if is a valid cmd
    Command interpretCMD(std::string);
    void addNewCMD(std::string,Command);
    void removeCMD(std::string);  
};

#endif
