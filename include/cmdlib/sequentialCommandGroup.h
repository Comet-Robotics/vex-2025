#ifndef __SEQUENTIAL_COMMAND_GROUP_H__
#define __SEQUENTIAL_COMMAND_GROUP_H__

#include "command.h"
#include <vector>
#include <initializer_list>

class SequentialCommandGroup : public Command {
  private:
    int currentCommandIndex = -1;

    std::vector<Command> m_commands;

  public:

    void AddCommands(const std::initializer_list<Command>& newCommands) {
        // m_commands.reserve(m_commands.size());
        m_commands.emplace_back(newCommands);
    }

    void SequentialCommandGroup(const std::initializer_list<Command>& commands) : Command() {
        AddCommands(commands);
    }

    virtual void Initialize() override {
       currentCommandIndex = 0;

        if (!m_commands.empty()) {
            m_commands.front()->initialize();
        }
    }
    
    
    virtual void Execute() override {
        if (m_commands.empty()) return;
        

        Command currentCommand = m_commands.at(currentCommandIndex);

        currentCommand->execute();
        if (!currentCommand->isFinished()) {
            currentCommand->end(false);

            currentCommandIndex++;
            if (currentCommandIndex < m_commands->size()) {
                m_commands.at(currentCommandIndex)->initialize();
            }
        }
    }
    
    
    virtual void End(bool interrupted) override {
        if (interrupted
                && !m_commands.empty()
                && currentCommandIndex > -1
                && currentCommandIndex < m_commands.size()) {
            m_commands.at(currentCommandIndex).end(true);
        }
        currentCommandIndex = -1;
    }
    
    virtual bool IsFinished() override { return currentCommandIndex == m_commands.size(); }
};


#endif