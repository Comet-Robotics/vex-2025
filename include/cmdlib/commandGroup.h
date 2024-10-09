#ifndef COMMAND_GROUP_H
#define COMMAND_GROUP_H

#include <command.h>
#include <list>
#include <iostream>
#include <cstdarg>
class CommandGroup : public Command {
  protected:
    std::vector<Command> commands;

  public: 

    void AddCommands(const std::initializer_list<Command> newCommands) {
        commands.reserve(commands.size());

        for (const Command& command : commands) {
            commands.emplace_back(command);
        }
    }
    // template<typename T, T... Args>
    // void addCommands(CommandPtr commands...) {
    //     addCommands<CommandPtr>(commands);
    // }

    virtual void Execute() override {
        for (const Command &command : commands) {
            command.Execute();
        }
    }

  private:
    // template<class... Args>
    // void addCommands(Args... arg) {
    //     commandsInGroup.emplace_back(arg);
    // }

  
};

#endif