#ifndef OFFLINEREADER_H
#define OFFLINEREADER_H

#include "../Course/location.h"

#include <iostream>
#include <memory>
#include <unordered_map>
#include <QString>
#include <vector>
#include <QFile>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

/**
 * @file
 * @brief Operations and data structures helps reading data from files
 */
namespace ReadData {

const int MAX_LOCATION_NUMBER = 9;
const int MAX_PLAYER_NUMBER = 4;

/**
 * @brief The LocationData struct
 */
struct LocationData {
    unsigned short id;
    QString name;
    QString img;
};

/**
 * @brief The CardData struct
 */
struct CardData {
    QString typeName;
    QString name;
    QString title;
    unsigned short amount;
    QString img;
};

/**
 * @brief The OfflineData struct holds initial data
 */
struct OfflineData {
    std::unordered_map<unsigned int, LocationData> locations;
    std::unordered_map<unsigned int, std::vector<CardData>> agentCards;
    std::vector<CardData> influenceCard;
    std::vector<CardData> initAgentCard;
};

/**
 * @brief The OfflineReader class to read files and store the data
 */
class OfflineReader
{
public:
    OfflineReader();

    /**
     * @brief readFileToData
     * @param locationFile, JSON file
     * @param cardFile, JSON file
     * @return share pointer to all struct Offline data, nullptr if file cannot read
     */
    std::shared_ptr<OfflineData> readFileToData(const QString& locationFile, const QString& agentCouncilerFile, const QString& influenceFile, const QString& initAgentFile);

private:
    std::shared_ptr<OfflineData> offlineData_;

    /**
     * @brief readLocationFile, read data of location
     * @param locationFile, JSON file
     */
    void readLocationFile(const QString& locationFile);

    /**
     * @brief readCardFile, read data of card for each location
     * @param cardFile, JSON file
     */
    void readCardFile(const QString& agentCouncilerFile);

    /**
     * @brief readInfluenceFile, read data of influence card
     * @param influenceFile, JSON file
     */
    void readInfluenceFile(const QString& influenceFile);

    /**
     * @brief readInitAgentFile, read data of initial agent cards
     * @param initAgentFile, JSON file
     */
    void readInitAgentFile(const QString &initAgentFile);
};

}

#endif // OFFLINEREADER_H
