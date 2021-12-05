#include "helper.h"


bool Utils::canGetMoreAgent(std::shared_ptr<Interface::Player> player, unsigned short maxAgent) {
    unsigned short count = 0;
    for (auto const& card: player->cards()) {
        if (card->typeName() == "Agent") {
            count++;
        }
    }
    return count < maxAgent;
}
