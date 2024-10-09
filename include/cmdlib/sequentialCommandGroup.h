#ifndef __SEQUENTIAL_COMMAND_GROUP_H__
#define __SEQUENTIAL_COMMAND_GROUP_H__

#include "commandGroup.h"
#include "command.h"

class SequentialCommandGroup : public CommandGroup {
  private:
    int currentCommandIndex = -1;
  public:
    virtual void Initialize() override {
       currentCommandIndex = 0;

        if (!commands.empty()) {
            commands.front().initialize();
        }
    }
    
    
    virtual void Execute() override {
        if (commands.empty()) return;
        

        CommandPtr currentCommand = commands.at(currentCommandIndex);

        currentCommand.execute();
        if (!currentCommand.isFinished()) {
            currentCommand.end(false);

            currentCommandIndex++;
            if (currentCommandIndex < commands.size()) {
                commands.at(currentCommandIndex).initialize();
            }
        }
    }
    
    
    virtual void End(bool interrupted) override {
        if (interrupted
                && !commands.empty()
                && currentCommandIndex > -1
                && currentCommandIndex < commands.size()) {
            commands.at(currentCommandIndex).end(true);
        }
        currentCommandIndex = -1;
    }
    
    virtual bool IsFinished() override { return currentCommandIndex == commands.size(); }
};


#endif