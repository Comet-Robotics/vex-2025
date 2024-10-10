
#ifndef COMMAND_H
#define COMMAND_H
#include <functional>
#include <memory>
#include "commandPtr.h"
#include 
// namespace commands {
    // #include "commandPtr.h"
/**
 * A state machine representing a complete action to be performed by the robot.
 * Commands are run by the CommandScheduler, and can be composed into
 * CommandGroups to allow users to build complicated multi-step actions without
 * the need to roll the state machine logic themselves.
 *
 * <p>Commands are run synchronously from the main robot loop; no
 * multithreading is used, unless specified explicitly from the command
 * implementation.
 *
 * <p>Note: ALWAYS create a subclass by extending CommandHelper<Base, Subclass>,
 * or decorators will not function!
 *
 * This class is provided by the NewCommands VendorDep
 *
 * @see CommandScheduler
 * @see CommandHelper
 */
class Command {
    public:
    ~Command();
    Command(const Command&) = default;
    Command& operator=(const Command& rhs);
    Command(Command&&) = default;
    Command& operator=(Command&&) = default;
    Command(Command&) = default;
        /**
     * The initial subroutine of a command.  Called once when the command is
     * initially scheduled.
     */
    virtual void Initialize();
    
    /**
     * The main body of a command.  Called repeatedly while the command is
     * scheduled.
     */
    virtual void Execute();
    
    /**
     * The action to take when the command ends.  Called when either the command
     * finishes normally, or when it interrupted/canceled.
     *
     * @param interrupted whether the command was interrupted/canceled
     */
    virtual void End(bool interrupted);
    
    /**
     * Whether the command has finished.  Once a command finishes, the scheduler
     * will call its end() method and un-schedule it.
     *
     * @return whether the command has finished.
     */
    virtual bool IsFinished() { return false; }
    
    /**
     * An enum describing the command's behavior when another command with a
     * shared requirement is scheduled.
     */
    enum class InterruptionBehavior {
        /**
         * This command ends, End(true) is called, and the incoming command is
         * scheduled normally.
         *
         * <p>This is the default behavior.
         */
        kCancelSelf,
        /** This command continues, and the incoming command is not scheduled. */
        kCancelIncoming
    };
    
    // friend class CommandPtr;
    
    /**
     * Decorates this command with a timeout. If the specified timeout is
     * exceeded before the command finishes normally, the command will be
     * interrupted and un-scheduled.
     *
     * @param duration the timeout duration
     * @return the command with the timeout added
     */
    [[nodiscard]]
    CommandPtr WithTimeout(double duration) &&;
    
    /**
     * Decorates this command with an interrupt condition. If the specified
     * condition becomes true before the command finishes normally, the command
     * will be interrupted and un-scheduled.
     *
     * @param condition the interrupt condition
     * @return the command with the interrupt condition added
     */
    [[nodiscard]]
    CommandPtr Until(std::function<bool()> condition) &&;
    
    /**
     * Decorates this command with a run condition. If the specified condition
     * becomes false before the command finishes normally, the command will be
     * interrupted and un-scheduled.
     *
     * @param condition the run condition
     * @return the command with the run condition added
     */
    [[nodiscard]]
    CommandPtr OnlyWhile(std::function<bool()> condition) &&;
    
    /**
     * Decorates this command with a runnable to run before this command starts.
     *
     * @param toRun the Runnable to run
     * @param requirements the required subsystems
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr BeforeStarting(std::function<void()> toRun) &&;
    
    /**
     * Decorates this command with a runnable to run after the command finishes.
     *
     * @param toRun the Runnable to run
     * @param requirements the required subsystems
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr AndThen(std::function<void()> toRun) &&;
    
    /**
     * Decorates this command to run repeatedly, restarting it when it ends, until
     * this command is interrupted. The decorated command can still be canceled.
     *
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr Repeatedly() &&;
    
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
    CommandPtr Unless(std::function<bool()> condition) &&;
    
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
    CommandPtr OnlyIf(std::function<bool()> condition) &&;
    

    
    /**
     * Decorates this command to have a different interrupt behavior.
     *
     * @param interruptBehavior the desired interrupt behavior
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr WithInterruptBehavior(InterruptionBehavior interruptBehavior) &&;
    
    /**
     * Decorates this command with a lambda to call on interrupt or end, following
     * the command's inherent End(bool) method.
     *
     * @param end a lambda accepting a boolean parameter specifying whether the
     * command was interrupted.
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr FinallyDo(std::function<void(bool)> end) &&;
    
    /**
     * Decorates this command with a lambda to call on interrupt or end, following
     * the command's inherent End(bool) method. The provided lambda will
     * run identically in both interrupt and end cases.
     *
     * @param end a lambda to run when the command ends, whether or not it was
     * interrupted.
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr FinallyDo(std::function<void()> end) &&;
    
    /**
     * Decorates this command with a lambda to call on interrupt, following the
     * command's inherent End(bool) method.
     *
     * @param handler a lambda to run when the command is interrupted
     * @return the decorated command
     */
    [[nodiscard]]
    CommandPtr HandleInterrupt(std::function<void()> handler) &&;
    
    
    /**
     * Schedules this command.
     */
    void Schedule();
    
    /**
     * Cancels this command. Will call End(true). Commands will be canceled
     * regardless of interruption behavior.
     */
    void Cancel();
    
    /**
     * Whether or not the command is currently scheduled. Note that this does not
     * detect whether the command is in a composition, only whether it is directly
     * being run by the scheduler.
     *
     * @return Whether the command is scheduled.
     */
    bool IsScheduled() const;
    
    /**
     * How the command behaves when another command with a shared requirement is
     * scheduled.
     *
     * @return a variant of InterruptionBehavior, defaulting to kCancelSelf.
     */
    virtual InterruptionBehavior GetInterruptionBehavior() const {
        return InterruptionBehavior::kCancelSelf;
    }
    
    /**
     * Transfers ownership of this command to a unique pointer.  Used for
     * decorator methods.
     */
    // virtual CommandPtr ToPtr() && {
    //     return std::make_unique<Command>(std::move(*this));
    // };
    
    protected:
    Command();
};
// }
#endif