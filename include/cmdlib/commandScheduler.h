#ifndef COMMAND_SCHEDULER_H
#define COMMAND_SCHEDULER_H

#include <unordered_set>

#include "command.h"
/**  CommandScheduler acts as a singleton which runs all the commands for the robot.
 *  This format allows for commands to be easily created, composed, and executed asynchronously 
 *  from when they are first scheduled.
 */
class CommandScheduler {
  private:
    static std::unordered_set<std::unique_ptr<Command>> scheduledCommands;
    static CommandScheduler* instance;

  public:
    
    CommandScheduler(int8_t startSize = 50) {

        if(instance != nullptr) throw "An instance of the Command Scheduler has already been created";
        
        instance = this;
        scheduledCommands.reserve(startSize);
    }

    static CommandScheduler& getInstance() { return *instance; }

    void Schedule(const std::unique_ptr<Command>& command) {
        if(!scheduledCommands.contains(command))
            scheduledCommands.emplace(command);
        
        command->Initialize();
    }

    bool IsScheduled (const std::unique_ptr<Command>& command) const {
        return scheduledCommands.contains(command);
    }


    void Cancel(const std::unique_ptr<Command>& command) {
        command->End(true);
        scheduledCommands.erase(command);
    }
    

    void run() { 
        for (const std::unique_ptr<Command>& command : scheduledCommands) {
            command->Execute();

            if (command->IsFinished()) {
                command->End(false);
                scheduledCommands.erase(command);
            }
        }
    }


};
#endif