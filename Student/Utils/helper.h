#include <qdebug.h>
#include <stdlib.h>
#include <QString>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <unordered_map>

#include "../course/Course/cardinterface.h"
#include "../course/Course/player.h"

namespace Utils {
const int MAX_CARD_IN_DECK = 14;

const QString LOCATION_FILE = ":/offlinedata/location.json";
const QString AGENT_COUNCILOR_FILE = ":/offlinedata/agentCouncilorCard.json";
const QString INFLUENCE_FILE = ":/offlinedata/influenceCard.json";
const QString INIT_AGENT_FILE = ":/offlinedata/initAgent.json";

/**
 * @brief The GameSetting struct
 */
struct GameSetting {
    int locations_;
    int game_duration_;
    int players_;
    std::vector<QString> name_;
};

const std::map<unsigned short, QString> INITIAL_AGENT_IMAGES = {
    {0, ":/cards/agent-player-1.png"},
    {1, ":/cards/agent-player-2.png"},
    {2, ":/cards/agent-player-3.png"},
    {3, ":/cards/agent-player-4.png"}
};

bool canGetMoreAgent(std::shared_ptr<Interface::Player> player, unsigned short maxAgent = 7);
}
