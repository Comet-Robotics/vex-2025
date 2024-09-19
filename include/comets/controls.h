#ifndef __COMETS_CONTROLS_H__
#define __COMETS_CONTROLS_H__

namespace comets
{
    /**
     * Simple detector that measures the current state of the robot and
     * preserves the previous state (updated each 'tick'). These states
     * are then used to compute rising and falling edges in boolean
     * signals.
     */
    class EdgeDetector
    {
    public:
        constexpr EdgeDetector() noexcept = default;

        inline constexpr void monitor(bool input) noexcept
        {
            previousInput = currentInput;
            currentInput = input;
        }

        inline constexpr bool getCurrent() const noexcept
        {
            return currentInput;
        }

        inline constexpr bool isPushed() const noexcept
        {
            return !previousInput && currentInput;
        }
        inline constexpr bool isReleased() const noexcept
        {
            return previousInput && !currentInput;
        }

    private:
        bool previousInput = false;
        bool currentInput = false;
    };
}

#endif
