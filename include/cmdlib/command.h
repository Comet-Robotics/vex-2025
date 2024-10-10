#ifndef COMMAND_H
#define COMMAND_H
#include <functional>
#include <memory>
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
    virtual InterruptionBehavior GetInterruptionBehavior() const;
    
    /**
     * Transfers ownership of this command to a unique pointer.  Used for
     * decorator methods.
     */
    
  protected:
    Command();
};
// }
#endif