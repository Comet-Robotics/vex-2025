#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "command.h"
#include "supplier.h"
#include "eventLoop.h"
class Trigger : Supplier<bool> {
  private:
    Supplier<bool> m_condition;
    EventLoop m_loop;
  public:
  
    Trigger(EventLoop& loop, Supplier<bool>& condition) {
        m_loop = loop;
        m_condition = condition;
    }

    Trigger(Supplier<bool> condition) {
        m_condition = condition;
    }

    Trigger& onTrue(Command command) {
        return this;
    }

    /**
     * Starts the given command whenever the condition changes from `true` to `false`.
     *
     * @param command the command to start
     * @return this trigger, so calls can be chained
     */
    Trigger& onFalse(Command command) {
        return this;
    }

    /**
     * Starts the given command when the condition changes to `true` and cancels it when the condition
     * changes to `false`.
     *
     * <p>Doesn't re-start the command if it ends while the condition is still `true`. If the command
     * should restart, see {@link edu.wpi.first.wpilibj2.command.RepeatCommand}.
     *
     * @param command the command to start
     * @return this trigger, so calls can be chained
     */
    Trigger& whileTrue(Command command) {
        return this;
    }

    /**
     * Starts the given command when the condition changes to `false` and cancels it when the
     * condition changes to `true`.
     *
     * <p>Doesn't re-start the command if it ends while the condition is still `false`. If the command
     * should restart, see {@link edu.wpi.first.wpilibj2.command.RepeatCommand}.
     *
     * @param command the command to start
     * @return this trigger, so calls can be chained
     */
    Trigger& whileFalse(Command command) {
        return this;
    }

    /**
     * Toggles a command when the condition changes from `false` to `true`.
     *
     * @param command the command to toggle
     * @return this trigger, so calls can be chained
     */
    Trigger& toggleOnTrue(Command command) {       
        return this;
    }

    /**
     * Toggles a command when the condition changes from `true` to `false`.
     *
     * @param command the command to toggle
     * @return this trigger, so calls can be chained
     */
    Trigger& toggleOnFalse(Command command) {
        return this;
    }

    inline bool operator()() const { return m_condition(); }

    
    /**
     * Composes two triggers with logical AND.
     *
     * @param trigger the condition to compose with
     * @return A trigger which is active when both component triggers are active.
     */
    inline Trigger& and(Supplier<bool>& other) {
        return new Trigger(new Supplier<bool>(){ return m_condition() && other(); });
    }

    /**
     * Composes two triggers with logical OR.
     *
     * @param trigger the condition to compose with
     * @return A trigger which is active when either component trigger is active.
     */
    inline Trigger& or(Supplier<bool> trigger) {
        return new Trigger(() -> m_condition.getAsBoolean() || trigger.getAsBoolean());
    }

    /**
     * Creates a new trigger that is active when this trigger is inactive, i.e. that acts as the
     * negation of this trigger.
     *
     * @return the negated trigger
     */
    inline Trigger& negate() {
        return new Trigger(() -> !m_condition.getAsBoolean());
    }  
};

#endif