#ifndef STRENGTHENCONNECTIONS_H
#define STRENGTHENCONNECTIONS_H

#include "../course/Course/actioninterface.h"
#include "../course/Course/random.h"
#include "agent.h"
#include "../course/Course/location.h"

/**
 * @file
 * @brief Action that represent strengthening connection of an agent
 */
namespace Action {

/**
 * @brief action strengthens connections of an agent
 */
class StrengthenConnections: public ActionInterface
{
public:
    /**
     * @brief StrengthenConnections constructor
     * @param agent, share pointer to the agent to strengthen connections
     * @pre -
     * @post Strengthen action created for the agent
     */
    explicit StrengthenConnections(std::shared_ptr<Interface::AgentInterface> agent, std::shared_ptr<Interface::Location> curLoc);

    /**
      * @brief default virtual destructor
      */
    virtual ~StrengthenConnections() = default;

    /**
     * @brief canPerform check if the agent is sent to some location
     * @pre -
     * @return true if the agent is being sent to some location
     * @post exception guarantee: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief perform
     * @pre -
     * @post connections of the agent is strengthened
     * @post exception guarantee: strong
     */
    virtual void perform();

private:
    std::shared_ptr<Interface::AgentInterface> agent_;
    std::shared_ptr<Interface::Location> loc_;
};

}

#endif // STRENGTHENCONNECTIONS_H
