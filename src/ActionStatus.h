#include <utility>

/**
 * @author Barbora Kolomazníková <kolombar@fit.cvut.cz>
 * @date 21.05.2021
 */

#pragma once

/**
 * @brief Status of the last taken action.
 * @details After every action taken by the user the resulting status is saved together with name of the action. We also store an error message in case of failure.
 */
class ActionStatus {
public:
    /**
     * @brief Possible action states - OK in case of success, ERROR in case of failure
     */
    enum class State {
        OK,
        ERROR,
    };

    ActionStatus() : state(State::OK) {};

    ActionStatus(std::string  action, const State & state, std::string message) : action(std::move(action)), state(state), message(std::move(message)) {};

    std::string GetAction() const;

    State GetState() const;

    std::string GetMessage() const;

private:
    std::string action;
    State state;
    std::string message;
};
