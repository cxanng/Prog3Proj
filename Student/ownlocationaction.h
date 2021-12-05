#ifndef OWNLOCATIONACTION_H
#define OWNLOCATIONACTION_H

#include <memory>

#include "../course/Course/actioninterface.h"
#include "../Course/location.h"
#include "../Course/councilor.h"
#include "../course/Course/deck.h"
#include "../Course/player.h"
#include "../Course/influence.h"

#include "agent.h"

/**
 * @file
 * @brief Action that represents owning a location
 */
namespace Action {

/**
 * @brief action owns a location
 */
class OwnLocationAction : public ActionInterface
{
public:
    /**
     * @brief OwnLocationAction constructior
     * @param player, share pointer to current player
     * @param targetLoc, share pointer to the target location
     * @post Own location action crated for the player
     */
    OwnLocationAction(std::shared_ptr<Interface::Player> player, std::shared_ptr<Interface::Location> targetLoc);

    /**
      * @brief default virtual destructor
      */
    virtual ~OwnLocationAction() = default;

    /**
     * @brief check if the own location action can be performed
     * @pre -
     * @return true if the player has any agent at location and the influence point of the player is higher than the needed one.
     * @post tell the player if the action can be done
     * @post Exception guarantee: nothrow
     */
    virtual bool canPerform() const;

    /**
     * @brief performs the suffle and draw action
     * @pre -
     * @post the owner of conciler is set to the current player.
     * @post Exception guarantee: strong
     */
    virtual void perform();

private:
    std::shared_ptr<Interface::Player> player_;
    std::shared_ptr<Interface::Location> location_;

    const int POINT_TO_OWN = 250;
    const int CONNECTION_TO_OWN = 10;
};

}

#endif // OWNLOCATIONACTION_H
