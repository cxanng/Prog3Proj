#ifndef CARDITEM_H
#define CARDITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <memory>
#include <QImage>
#include <QString>
#include <QToolTip>

#include "../course/Course/cardinterface.h"
#include "../course/Course/influence.h"
#include "../course/Course/councilor.h"
#include "../course/Course/player.h"
#include "../course/Course/location.h"
#include "../course/Course/game.h"

#include "agent.h"

/**
 * @file
 * @brief Implement a graphic object to represent a card
 */
namespace Ui {
class CardInterface;
}

/**
 * @brief The CardItem class implement a graphic object to represent a card
 */
class CardItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    /**
     * @brief CardItem Constructor
     * @param name, card name
     * @param card, weak pointer to card interface
     * @param description, description of the card
     * @param img, path of the card's background image
     * @param parent, parent object
     */
    explicit CardItem(QString name, std::shared_ptr<Interface::CardInterface> card, std::shared_ptr<Interface::Game> game, QString description = "", QString img = "", QObject *parent = nullptr);

    /**
     * @brief boundingRect
     * @return a bounding Rectangle object
     */
    QRectF boundingRect() const override;

    /**
     * @brief paint, paint function to render the card
     * @param painter, QPainter object
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief setBackgroud, set card's background
     * @param img, path to the image
     */
    void setBackgroud(QString img);

    /**
     * @brief getCard
     * @return share pointer to the card
     */
    std::shared_ptr<Interface::CardInterface> getCard();

private:
    int mHeight = 200;
    int mWidth = 140;
    int mPaddingX = 20;
    int mPaddingY = 20;
    QColor mColor = Qt::white;
    QString mName;
    std::shared_ptr<Interface::CardInterface> mCard;
    QString mDesc;
    QString backGround;
    std::shared_ptr<Interface::Game> game_;


protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};

#endif // CARDITEM_H
