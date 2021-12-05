#ifndef AGENT_H
#define AGENT_H

#include "../course/Course/agentinterface.h"
#include <QDebug>

/**
 * @file
 * @brief Implement cards that represent agents
 */
using namespace Interface;

namespace CardModel {

/**
 * @brief The Agent class represent agents
 * Inherits from AgentInterface
 */
class Agent: public AgentInterface
{
public:
    /**
     * @brief Agent Constructor
     * @param name, Agent's name
     * @param title, Agent'title
     * @param common, tell if this is generic
     * @param owner, null ptr if no one own the card at the begining of game
     * @post Agent has given name, title, common, owner if possible, no location, no placement, no connections.
     */
    explicit Agent(const QString &name, const QString &title, bool common = false);
    ~Agent();

    /**
     * @brief typeName, return the type of the card
     * @pre-
     * @return card type as string
     * @post exception guarantee: nothrow
     */
    QString typeName() const;
    /**
     * @brief name, get the name of the card
     * @pre-
     * @return name as the string
     */
    QString name() const;

    /**
     * @brief title, get the title of the card
     * @pre-
     * @return title of the agent as string
     * @post exception guarantee: no-throw
     */
    QString title() const;

    /**
     * @brief location, tell which location the card related to
     * @pre-
     * @return weak pointer to the location, null ptr if none
     * @post exception guaratee: no-throw
     */
    std::weak_ptr<Location> location() const;

    /**
     * @brief owner, tell who owns the card
     * @pre-
     * @return weak ptr to the owner of the card, null ptr if none
     * @post exception guarantee: no-throw
     */
    std::weak_ptr<Player> owner() const;

    /**
     * @brief setOwner, set owner to the card
     * @pre-
     * @param owner, weak pointer to new owner of the card, or empty if removed fron possession
     * @post: card has new owner or no one owns the card.
     * @post exception guarantee: nothrow
     */
    void setOwner(std::weak_ptr<Player> owner);

    /**
     * @brief isCommon, tells if this is a common/"generic" agent with no relation to any location
     * @pre -
     * @return true, if generic
     */
    bool isCommon() const;

    /**
     * @brief placement, return info about the agent's placement
     * @pre -
     * @return weak_ptr to the location agent is in, or empty ptr if not on board
     * @post exception guarantee: nothrow
     */
    std::weak_ptr<Location> placement() const;

    /**
     * @brief setPlacement, set new placement for the agent
     * @pre -
     * @param placement location, empty if not on board
     * @post new location is set to the agent
     * @post exception guarantee: no-throw
     */
    void setPlacement(std::weak_ptr<Location> placement);

    /**
     * @brief connections, tell about the current connection state of agent and location
     * @pre -
     * @return current level of connrections
     * @post exception guarantee: no-throw
     */
    unsigned short connections() const;

    /**
     * @brief setConnections, set new connection level to the agent
     * @pre-
     * @param connections, new connection level of connections level
     * @post new connection is set according to the given param
     * @post guarantee exception: strong
     * @exception StateException if variant would be broken
     */
    void setConnections(unsigned short connections);

    /**
     * @brief modifyConncetions, change the amount of connection
     * @pre-
     * @param change, the given amount to change the connection
     * @post connection level is changed according to the  given params
     */
    void modifyConnections(short change);

private:
    QString name_;
    QString title_;
    bool common_;
    std::weak_ptr<Location> location_;

    std::weak_ptr<Location> placement_;

    std::weak_ptr<Player> owner_;
    unsigned short connections_;
};

}

#endif // AGENT_H
