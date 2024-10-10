#ifndef __PARALLEL_COMMAND_GROUP_H__
#define __PARALLEL_COMMAND_GROUP_H__

#include "command.h"
#include <unordered_map>

class ParallelCommandGroup : public Command {
  private:
    std::unordered_map<Command, bool> m_commands;
    int m_runningCommandCount = 0;
  public:


    void AddCommands(std::initializer_list<Command>& newCommands) {
        m_commands.reserve(newCommands.size());

        for (const Command& command : newCommands) {
            m_commands.try_emplace(command, false);
        }
    }

    ParallelCommandGroup(std::initializer_list<Command>& commands) {
        AddCommands(commands);
    }

    virtual void Initialize() override {
        for (std::pair<Command, bool>& node: m_commands) {
            node.first->Initialize();
            node.second = true;
            m_runningCommandCount++;
        }  
    }
    
    
    virtual void Execute() override {
        for (std::pair<Command, bool>& commandNode: m_commands) {
            if(commandNode.second) continue;

            commandNode.first.Execute();

            if(commandNode.first.IsFinished()) {
                commandNode.first.End();
                commandNode.second = false;
                m_runningCommandCount--;
            }
        } 
    }   
    
    
    virtual void End(bool interrupted) override {
        if (!interrupted) return;
    
        for (std::pair<Command, bool> &commandNode : m_commands) {
            if (!commandNode.second) return 
            
            commandNode.first.End(true);
            commandNode.second = false;
            m_runningCommandCount--;
        }
    }
    
   
    virtual bool IsFinished() { return m_runningCommandCount == 0; }
};

#endif