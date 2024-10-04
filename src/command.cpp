#include "command.h"
/**
     * Decorates this command with a timeout. If the specified timeout is
     * exceeded before the command finishes normally, the command will be
     * interrupted and un-scheduled.
     *
     * @param duration the timeout duration
     * @return the command with the timeout added
     */
    [[nodiscard]]
    CommandPtr Command::WithTimeout(double duration) && {
       
    }
    
    /**
     * Decorates this command with an interrupt condition. If the specified
     * condition becomes true before the command finishes normally, the command
     * will be interrupted and un-scheduled.
     *
     * @param condition the interrupt condition
     * @return the command with the interrupt condition added
     */
    [[nodiscard]]
    CommandPtr Command::Until(std::function<bool()> condition) && {

    }
    
    /**
     * Decorates this command with a run condition. If the specified condition
     * becomes false before the command finishes normally, the command will be
     * interrupted and un-scheduled.
     *
     * @param condition the run condition
     * @return the command with the run condition added
     */
    [[nodiscard]]
    CommandPtr Command::OnlyWhile(std::function<bool()> condition) && {
        
    }
    
    /**
     * Decorates this command with a runnable to run before this command starts.
     *
     * @param toRun the Runnable to run
     * @param requirements the required subsystems
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::BeforeStarting(std::function<void()> toRun) && {

    }
    
    /**
     * Decorates this command with a runnable to run after the command finishes.
     *
     * @param toRun the Runnable to run
     * @param requirements the required subsystems
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::AndThen(std::function<void()> toRun) && {

    }
    
    /**
     * Decorates this command to run repeatedly, restarting it when it ends, until
     * this command is interrupted. The decorated command can still be canceled.
     *
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::Repeatedly() && {

    }
    
    /**
     * Decorates this command to only run if this condition is not met. If the
     * command is already running and the condition changes to true, the command
     * will not stop running. The requirements of this command will be kept for
     * the new conditional command.
     *
     * @param condition the condition that will prevent the command from running
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::Unless(std::function<bool()> condition) && {

    }
    
    /**
     * Decorates this command to only run if this condition is met. If the command
     * is already running and the condition changes to false, the command will not
     * stop running. The requirements of this command will be kept for the new
     * conditional command.
     *
     * @param condition the condition that will allow the command to run
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::OnlyIf(std::function<bool()> condition) && {

    }
    

    
    /**
     * Decorates this command to have a different interrupt behavior.
     *
     * @param interruptBehavior the desired interrupt behavior
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::WithInterruptBehavior(
        Command::InterruptionBehavior interruptBehavior) && {

        }
    
    /**
     * Decorates this command with a lambda to call on interrupt or end, following
     * the command's inherent Command::End(bool) method.
     *
     * @param end a lambda accepting a boolean parameter specifying whether the
     * command was interrupted.
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::FinallyDo(std::function<void(bool)> end) && {

    }
    
    /**
     * Decorates this command with a lambda to call on interrupt or end, following
     * the command's inherent Command::End(bool) method. The provided lambda will
     * run identically in both interrupt and end cases.
     *
     * @param end a lambda to run when the command ends, whether or not it was
     * interrupted.
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::Command::FinallyDo(std::function<void()> end) && {
        
    }
    
    /**
     * Decorates this command with a lambda to call on interrupt, following the
     * command's inherent Command::End(bool) method.
     *
     * @param handler a lambda to run when the command is interrupted
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Command::HandleInterrupt(std::function<void()> handler) && {

    }
    
    
    /**
     * Schedules this command.
     */
    void Command::Schedule() {
        CommandScheduler::getInstance().Schedule(this);
    }
    
    /**
     * Cancels this command. Will call End(true). Commands will be canceled
     * regardless of interruption behavior.
     */
    void Command::Cancel() {
        CommandScheduler::getInstance().Cancel(this);
    }
    
    /**
     * Whether or not the command is currently scheduled. Note that this does not
     * detect whether the command is in a composition, only whether it is directly
     * being run by the scheduler.
     *
     * @return Whether the command is scheduled.
     */
    bool Command::IsScheduled() const {
        return CommandScheduler::getInstance().IsScheduled(this);
    };