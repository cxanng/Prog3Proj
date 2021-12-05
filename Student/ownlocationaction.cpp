#include "ownlocationaction.h"
#include "Utils/helper.h"
namespace Action {

OwnLocationAction::OwnLocationAction(std::shared_ptr<Player> player, std::shared_ptr<Location> targetLoc):
    player_(player),
    location_(targetLoc)
{

}

bool OwnLocationAction::canPerform() const
{
    qDebug() << "Called canPerform";
    bool canOwn = false;

    for (auto const& agent: location_->agents()) {
        if (agent->owner().lock() == player_) {
            if (location_->influence(player_) >= POINT_TO_OWN && agent->connections() >= CONNECTION_TO_OWN){
                qDebug() << "Can own this location: " + location_->name();
                canOwn = true;
                break;
            } else {
                qDebug() << "Influence point or connections does not enough, can not own this location: " + location_->name();
            }
        }
    }

    return canOwn;
}

void OwnLocationAction::perform()
{
    location_->councilor()->setOwner(player_);
    while(location_->deck()->size() != 0) {
        if (!Utils::canGetMoreAgent(player_) && location_->deck()->peek()->typeName() == "Agent") {
            qDebug() << "Max number of agents reached, draw card later";
            location_->deck()->shuffle();
            if (location_->deck()->size() == 1) {
                break;
            }
        } else {
            auto card = location_->deck()->draw();
            player_->addCard(card);
            if (card->typeName() == "Influence") {
                std::shared_ptr<Interface::Influence> influenceCard = std::static_pointer_cast<Interface::Influence>(card);
                location_->setInfluence(player_, location_->influence(player_) + influenceCard->amount());
            }
        }
    }
}

} // Action
