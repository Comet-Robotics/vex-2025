#ifndef __SEQUENTIAL_COMMAND_GROUP_H__
#define __SEQUENTIAL_COMMAND_GROUP_H__

#include "commandGroup.h"

class SequentialCommandGroup : public CommandGroup {
public:
    virtual void Initialize() override {

    }
    
    
    virtual void Execute() override {

    }
    
    
    virtual void End(bool interrupted) override {

    }
    
   
    virtual bool IsFinished() { return false; }
};


#endif