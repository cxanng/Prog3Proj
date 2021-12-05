#ifndef SHUFFLEANDDRAWACTION_H
#define SHUFFLEANDDRAWACTION_H

#include "../course/Course/actioninterface.h"
#include "../course/Course/deck.h"
#include "agent.h"
#include <memory>

/**
 * @file
 * @brief Action represents shuffling and drawing a card from a deck to player's hand
 */
namespace Action {

/**
 * @brief action shuffles and draws a card from location's deck to player's hand
 */
class ShuffleAndDrawAction: public ActionInterface
{
public:
    /**
     * @brief SuffleAndDrawAction
     * @param agent, shared_ptr to the agent
     * @param targetLoc, shared_ptr to the target location
     * @pre -
     * @post Shuffle action created
     */
    explicit ShuffleAndDrawAction(std::shared_ptr<Interface::Player> player, std::shared_ptr<Interface::Location> targetLoc);

    /**
     * @brief default virtual destructor
     */
    virtual ~ShuffleAndDrawAction() = default;

    /**
     * @brief check if the draw action can be performed
     * @pre -
     * @return true if the player has any agent at location and the deck at that location can be drawed
     * @post exception guarantee: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief performs the suffle and draw action
     * @pre -
     * @post a card from location deck has be drawed to player's hand
     * @post exception guarantee: strong
     */
    virtual void perform();
private:
    std::shared_ptr<Interface::Player> player_;
    std::shared_ptr<Interface::Location> loc_;
};

}


#endif // SHUFFLEANDDRAWACTION_H
