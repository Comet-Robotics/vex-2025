#ifndef COMMAND_PTR_H
#define COMMAND_PTR_H

#include <memory>
#include "command.h"
#include <concepts>
// using namespace commands;
class CommandPtr : public std::unique_ptr<Command> {

 public:

    explicit CommandPtr(std::unique_ptr<Command>&& command);
    
    template <std::derived_from<Command> T>
    explicit CommandPtr(T&& command)
        : CommandPtr(
                std::make_unique<std::decay_t<T>>(std::forward<T>(command))) {}

    CommandPtr(CommandPtr&&);
    CommandPtr& operator=(CommandPtr&&) = default;
    
    explicit CommandPtr(std::nullptr_t) = delete;
};

#endif
