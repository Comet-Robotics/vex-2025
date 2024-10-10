#ifndef COMMAND_SCHEDULER_H
#define COMMAND_SCHEDULER_H

#include "commandPtr.h"
#include <unordered_set>

/**  CommandScheduler acts as a singleton which runs all the commands for the robot.
 *  This format allows for commands to be easily created, composed, and executed asynchronously 
 *  from when they are first scheduled.
 */
class CommandScheduler {
  private:
    static std::unordered_set<CommandPtr> scheduledCommands;
    static CommandScheduler* instance;

  public:
    
    CommandScheduler() {

        if(instance != nullptr) throw "An instance of the Command Scheduler has already been created";
        
        instance = this;
        scheduledCommands.reserve(50);
    }


    static CommandScheduler& getInstance() { return *instance; }

    void CommandScheduler::Schedule(CommandPtr command) {
        if(!scheduledCommands.contains(command))
            scheduledCommands.emplace(command);


        // if (scheduledCommands.contains(command) ||
        //     (frc::RobotState::IsDisabled() && !command->RunsWhenDisabled())) {
        //     return;
        // }

        command->Initialize();
    }

    bool CommandScheduler::IsScheduled (CommandPtr command) const {
        return scheduledCommands.contains(command);
    }


    void CommandScheduler::Cancel(CommandPtr command) {
        command->End(true);
        scheduledCommands.erase(command);
    }
    


    void run() { 
        for (const CommandPtr &command : scheduledCommands) {
            command->Execute();

            if (command->IsFinished()) {
                command->End(false);
                scheduledCommands.erase(command);
            }
        }
        
        // scheduledCommands.remove_if([](CommandPtr cmd) { return cmd->IsFinished(); });
        
        
        // for (int i = 0; i < scheduledCommands.size(); i++) {
        //     command = std::make_unique<Command>(scheduledCommands.at(i));
        //     command->Execute();

        //     if (command->IsFinished()) {
        //         scheduledCommands.remove(scheduledCommands.begin() + i);
        //         command->End(false);
        //     }
        // }
    }


};
#endif