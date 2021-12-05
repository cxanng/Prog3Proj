#include "agent.h"
#include "../course/Course/stateexception.h"
#include "../course/Course/rangeexception.h"

using std::weak_ptr;

namespace CardModel {

Agent::Agent(const QString &name, const QString &title, bool common):
    name_(name),
    title_(title),
    common_(common),
    location_(),
    owner_(),
    connections_(0)
{
    try {
        if (name == "") {
            throw Interface::StateException("Name cannot be empty");
        }
    }  catch (Interface::StateException& e) {
        qDebug() << e.msg();
        name_ = "Default agent name";
    }

    try {
        if (title == "") {
            throw Interface::StateException("Title cannot be empty");
        }
    }  catch (Interface::StateException& e) {
        qDebug() << e.msg();
        title_ = "Default agent title";
    }
}

Agent::~Agent() {

}

QString Agent::typeName() const
{
    return "Agent";
}

QString Agent::name() const
{
    return name_;
}

QString Agent::title() const
{
    return title_;
}

weak_ptr<Interface::Location> Agent::location() const
{
    return location_;
}

weak_ptr<Player> Agent::owner() const
{
    return owner_;
}

void Agent::setOwner(std::weak_ptr<Interface::Player> owner)
{
    owner_ = owner;
}

bool Agent::isCommon() const
{
    return common_;
}

weak_ptr<Location> Agent::placement() const
{
    return placement_;
}

void Agent::setPlacement(std::weak_ptr<Interface::Location> placement)
{
    placement_ = placement;
}

unsigned short Agent::connections() const
{
    return connections_;
}

void Agent::setConnections(unsigned short connections)
{
    connections_ = connections;
}

void Agent::modifyConnections(short change)
{
    try {
        if (connections_ + change < 0) {
            throw Interface::RangeException("Connections reach negative after modify");
        }
        connections_ = (unsigned short)(connections_ + change);
    }  catch (Interface::RangeException& e) {
        qDebug() << e.msg();
    }
}
}
