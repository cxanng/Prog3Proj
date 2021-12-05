#include "strengthenconnections.h"

namespace Action {

StrengthenConnections::StrengthenConnections(std::shared_ptr<Interface::AgentInterface> agent, std::shared_ptr<Interface::Location> curLoc):
    agent_(agent), loc_(curLoc)
{

}

bool StrengthenConnections::canPerform() const {
    return agent_->placement().lock() == loc_;
}

void StrengthenConnections::perform() {
    agent_->setConnections(agent_->connections() + Random::RANDOM.die());
}

} // Action
