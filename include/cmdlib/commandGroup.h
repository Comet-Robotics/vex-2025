#ifndef COMMAND_GROUP_H
#define COMMAND_GROUP_H

#include <command.h>
#include <list>
#include <iostream>
#include <cstdarg>
class CommandGroup : public Command {
  protected:
    std::vector<CommandPtr> commandsList;
  public: 
    template<typename T, T... Args>
    void addCommands(CommandPtr commands...) {
        addCommands<CommandPtr>(commands);
    }

  private:
    template<class... Args>
    void addCommands(Args... arg) {
        commandsList.emplace_back(arg);
    }
};

#endif