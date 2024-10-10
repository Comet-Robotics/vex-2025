#ifndef __SEQUENTIAL_COMMAND_GROUP_H__
#define __SEQUENTIAL_COMMAND_GROUP_H__

#include "command.h"
#include <vector>
#include <initializer_list>

class SequentialCommandGroup : public Command {
  private:
    int currentCommandIndex = -1;

    std::vector<std::unique_ptr<Command>> m_commands;

  public:

    void AddCommands(std::initializer_list<Command>& newCommands) {
        m_commands.reserve(m_commands.size());

        for (const Command& command : newCommands) {
            m_commands.emplace_back(std::make_unique<Command>(command));
        }
    }

    SequentialCommandGroup(std::initializer_list<Command>&& commands) {
        AddCommands(commands);
    }

    virtual void Initialize() override {
       currentCommandIndex = 0;

        if (!m_commands.empty()) {
            m_commands.front()->Initialize();
        }
    }
    
    
    virtual void Execute() override {
        if (m_commands.empty()) return;
        

        auto& currentCommand = m_commands.at(currentCommandIndex);

        currentCommand->Execute();
        if (!currentCommand->IsFinished()) {
            currentCommand->End(false);

            currentCommandIndex++;
            if (currentCommandIndex < m_commands.size()) {
                m_commands.at(currentCommandIndex)->Initialize();
            }
        }
    }
    
    
    virtual void End(bool interrupted) override {
        if (interrupted
                && !m_commands.empty()
                && currentCommandIndex > -1
                && currentCommandIndex < m_commands.size()) {
            m_commands.at(currentCommandIndex)->End(true);
        }
        currentCommandIndex = -1;
    }
    
    virtual bool IsFinished() override { return currentCommandIndex == m_commands.size(); }
};


#endif