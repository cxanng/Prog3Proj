#include "sendagentaction.h"
#include "../course/Course/location.h"
#include "player.h"

namespace Action {

SendAgentAction::SendAgentAction(std::shared_ptr<Interface::AgentInterface> agent, std::shared_ptr<Interface::Location> targetLoc):
    agent_(agent), loc_(targetLoc)
{
}

bool SendAgentAction::canPerform() const
{
    qDebug() << "called canPerform";
    bool canSent = true;
    for (auto const& agent: loc_->agents()) {
        if (agent->owner().lock().get() == agent_->owner().lock().get()) {
            canSent = false;
        }
    }
    return (agent_->owner().lock() != nullptr
            && agent_->placement().lock() == nullptr
            && canSent);
}

void SendAgentAction::perform() {
    qDebug() << "perform";
    loc_->sendAgent(agent_);
    agent_->setConnections(0);
    agent_->owner().lock()->playCard(agent_);
}

} // Action
