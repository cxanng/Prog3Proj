#include "shuffleanddrawaction.h"
#include "../course/Course/location.h"
#include "player.h"
#include "influence.h"
#include "Utils/helper.h"
#include "cardpreviewdialog.h"

namespace Action {

ShuffleAndDrawAction::ShuffleAndDrawAction(std::shared_ptr<Interface::Player> player, std::shared_ptr<Interface::Location> targetLoc):
    player_(player), loc_(targetLoc)
{

}

bool ShuffleAndDrawAction::canPerform() const {
    qDebug() << "called canPerform";
    bool canDraw = false;
    for (auto const& agent: loc_->agents()) {
        if (agent->owner().lock() == player_) {
            canDraw = true;
        }
    }
    return canDraw && loc_->deck()->canDraw();
};

void ShuffleAndDrawAction::perform() {
    loc_->deck()->shuffle();
    if (!Utils::canGetMoreAgent(player_) && loc_->deck()->size() != 1) {
        while (loc_->deck()->peek()->typeName() == "Agent") {
            loc_->deck()->shuffle();
        }
    } else if (!Utils::canGetMoreAgent(player_) && loc_->deck()->size() == 1) {
        return;
    }
    std::shared_ptr<Interface::CardInterface> newCard = loc_->deck()->draw();
    player_->addCard(newCard);
    std::shared_ptr<Interface::Influence> influenceCard = std::static_pointer_cast<Interface::Influence>(newCard);
    if (influenceCard) {
        unsigned short currentInfluence = loc_->influence(player_);
        loc_->setInfluence(player_, currentInfluence + influenceCard->amount());
    }
};

} // Action
