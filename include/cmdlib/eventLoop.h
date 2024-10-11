#ifndef __EVENT_LOOP_H__
#define __EVENT_LOOP_H__

#include <set>
#include <functional>
class EventLoop {
  private:
    std::vector<std::function<void()>> m_events;
  public:
    EventLoop() = default;

    void bind(std::function<void()> action) {
        m_events.add(action);
        
    }

    void poll() {
        for (auto& action : m_events) {
            action();
        }
    }

    void clear() {
        m_events.clear();
    }
};
#endif