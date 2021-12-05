#include "offlinereader.h"

namespace ReadData {

OfflineReader::OfflineReader()
{

}

std::shared_ptr<OfflineData> OfflineReader::readFileToData(const QString &locationFile, const QString &agentCouncilerFile, const QString& influenceFile, const QString& initAgentFile)
{
    offlineData_ = std::make_shared<OfflineData>();
    readLocationFile(locationFile);
    readCardFile(agentCouncilerFile);
    readInfluenceFile(influenceFile);
    readInitAgentFile(initAgentFile);
    return offlineData_;
}

void OfflineReader::readLocationFile(const QString &locationFile)
{
    QString filecontent;
    QFile file;

    file.setFileName(locationFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filecontent = file.readAll();
    file.close();

    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(filecontent.toUtf8(), &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing location JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject o = jsonArray.at(i).toObject();
        unsigned short id = o.value("id").toString().toInt();
        QString name = o.value("name").toString();
        QString img = o.value("img").toString();
        offlineData_->locations.insert({id, {id, name, img}});
    }
}

void OfflineReader::readCardFile(const QString &agentCouncilerFile)
{
    QString filecontent;
    QFile file;

    file.setFileName(agentCouncilerFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filecontent = file.readAll();
    file.close();

    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(filecontent.toUtf8(), &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing agent and councilor JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

    for (int i = 0; i < MAX_LOCATION_NUMBER; i++) {
        std::vector<CardData> init_card_v;
        offlineData_->agentCards.insert({i, init_card_v});
    }

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject o = jsonArray.at(i).toObject();
        unsigned short location_id = o.value("location_id").toString().toInt();
        QString typeName = o.value("typename").toString();
        QString name = o.value("name").toString();
        QString title = o.value("title").toString();
        QString img = o.value("img").toString();
        offlineData_->agentCards[location_id].push_back({typeName, name, title, 0, img});
    }
}

void OfflineReader::readInfluenceFile(const QString &influenceFile)
{
    QString filecontent;
    QFile file;

    file.setFileName(influenceFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filecontent = file.readAll();
    file.close();

    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(filecontent.toUtf8(), &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing influence JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject o = jsonArray.at(i).toObject();
        QString typeName = o.value("typename").toString();
        QString name = o.value("name").toString();
        unsigned short amount = o.value("amount").toString().toInt();
        QString img = o.value("img").toString();
        offlineData_->influenceCard.push_back({typeName, name, "", amount, img});
    }
}

void OfflineReader::readInitAgentFile(const QString &initAgentFile)
{
    QString filecontent;
    QFile file;

    file.setFileName(initAgentFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    filecontent = file.readAll();
    file.close();

    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(filecontent.toUtf8(), &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing influence JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonObject o = jsonArray.at(i).toObject();
        QString name = o.value("name").toString();
        QString img = o.value("img").toString();
        QString title = o.value("title").toString();
        offlineData_->initAgentCard.push_back({"Agent", name, title, 0, img});
    }
}

}
