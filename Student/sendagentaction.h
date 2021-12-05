#ifndef SENDAGENTACTION_H
#define SENDAGENTACTION_H

#include "../course/Course/actioninterface.h"
#include "agent.h"
#include <memory>

/**
 * @file
 * @brief Action that represents agent sending to a location
 */
namespace Action {

/**
 * @brief Action sends an agent to a location
 */
class SendAgentAction: public ActionInterface
{
public:
    /**
     * @brief Constructor
     * @param agent shared_ptr to the agent
     * @param targetLoc shared_ptr to the target location
     * @post Send agent action created for the agent
     */
    explicit SendAgentAction(std::shared_ptr<Interface::AgentInterface> agent, std::shared_ptr<Interface::Location> targetLoc);

    /**
     * @brief default virtual destructor
     */
    virtual ~SendAgentAction() = default;

    /**
     * @brief check if the agent can be sent to location
     * @pre -
     * @return true if the agent is on player's deck and location still receive agent
     * @post exception guarantee: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief performs the send agent action
     * @pre -
     * @post agent has been sent to the location from owner's hand
     * @post exception guarantee: strong
     */
    virtual void perform();

private:
    std::shared_ptr<Interface::AgentInterface> agent_;
    std::shared_ptr<Interface::Location> loc_;

};

} // Interface


#endif // SENDAGENTACTION_H
