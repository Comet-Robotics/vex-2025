#ifndef __PARALLEL_COMMAND_GROUP_H__
#define __PARALLEL_COMMAND_GROUP_H__

#include "command.h"
#include <unordered_map>

class ParallelCommandGroup : public Command {
  private:
    struct CommandNode {
        std::unique_ptr<Command> command;
        bool isRunning;
    };
    std::vector<CommandNode> m_commands;
    int m_runningCommandCount = 0;

  public:
    void AddCommands(std::vector<std::unique_ptr<Command>>&& newCommands) {
        m_commands.reserve(newCommands.size());
        for (auto& command : newCommands) {
            // Move each command into a new CommandNode and add it to m_commands
            m_commands.emplace_back({std::move(command), false});
        }
    }

    void AddCommands(std::initializer_list<Command>& newCommands) {
        m_commands.reserve(newCommands.size());
        for (auto& command : newCommands) {
            // Move each command into a new CommandNode and add it to m_commands
            m_commands.emplace_back({std::make_unique<Command>(command), false});
        }
    }
    // void AddCommands(std::initializer_list<Command>& newCommands) {
    //     m_commands.reserve(newCommands.size());

    //     for (const Command& command : newCommands) {
    //         m_commands.try_emplace(command, false);
    //     }
    // }

    ParallelCommandGroup(std::initializer_list<Command>&& commands) {
        AddCommands(commands);
    };
  


    virtual void Initialize() override {
        for (CommandNode &node: m_commands) {
            node.command->Initialize();
            node.isRunning = true;
            m_runningCommandCount++;
        }  
    }
    
    
    virtual void Execute() override {
        for (CommandNode& commandNode: m_commands) {
            if(commandNode.isRunning) continue;

            commandNode.command->Execute();

            if(commandNode.command->IsFinished()) {
                commandNode.command->End(false);
                commandNode.isRunning = false;
                m_runningCommandCount--;
            }
        } 
    }   
    
    
    virtual void End(bool interrupted) override {
        if (!interrupted) return;
    
        for (CommandNode& commandNode : m_commands) {
            if (!commandNode.isRunning) return 
            
            commandNode.command->End(true);
            commandNode.isRunning = false;
            m_runningCommandCount--;
        }
    }
    
   
    virtual bool IsFinished() { return m_runningCommandCount == 0; }
};

#endif