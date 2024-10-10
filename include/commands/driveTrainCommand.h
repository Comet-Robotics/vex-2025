#ifndef DRIVE_TRAIN_COMMAND_H
#define DRIVE_TRAIN_COMMAND_H

#include <command.h>
#include <subsystems.h>
#include "supplier.h"
class DriveBaseCommand : Command {
  private:
    Drivebase& m_drivebase;
    Supplier<double>& m_throttleSup;
    Supplier<double>& m_rotationSup;
  public:
    DriveBaseCommand(Drivebase& drivebase, Supplier<double>& throttleSupplier, Supplier<double>& rotationSupplier) {
        m_drivebase = drivebase;
        m_throttleSup = throttleSupplier;
        m_rotationSup = rotationSupplier;
    }

    virtual void Execute() override {
        m_drivebase.errorDrive(m_throttleSup(), m_rotationSup());
    }

    
};
#endif