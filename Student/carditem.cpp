#include "carditem.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

CardItem::CardItem(QString name, std::shared_ptr<Interface::CardInterface> card, std::shared_ptr<Interface::Game> game, QString description, QString img, QObject *parent):
      mName(name), mCard(card), mDesc(description), backGround(img), game_(game)
{
    Q_UNUSED(parent);
    setAcceptHoverEvents(true);
}

QRectF CardItem::boundingRect() const
{
    return QRectF(0, 0, mWidth, mHeight);
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rect = boundingRect();
    painter->setBrush(QBrush(mColor));
    painter->drawRect(rect);
    if (backGround != "") {
        painter->drawImage(rect, QImage(backGround));
    } else {
        painter->drawText(mPaddingX, mPaddingY, mName);
        painter->drawText(mPaddingX, mPaddingY * 3, mDesc);
    }
}

std::shared_ptr<Interface::CardInterface> CardItem::getCard()
{
    return mCard;
}

void CardItem::setBackgroud(QString img) {
    backGround = img;
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (mCard) {
        QString toolTipString;
        std::shared_ptr<Interface::Influence> influenceCard = std::dynamic_pointer_cast<Interface::Influence>(mCard);
//        std::shared_ptr<CardModel::Agent> agentCard = std::dynamic_pointer_cast<CardModel::Agent>(mCard);
        if (influenceCard) {
            toolTipString = "Card type: " + influenceCard->typeName() + "\nName: " + influenceCard->name() + "\nAmount: " + QString::number(influenceCard->amount());
        } else if (mCard->typeName() == "Agent") {
            if (mCard->owner().lock()) {
                std::shared_ptr<CardModel::Agent> agentCard = std::dynamic_pointer_cast<CardModel::Agent>(mCard);
                toolTipString = "Card type: " + agentCard->typeName()
                        + "\nName: " + agentCard->name()
                        + "\n" + agentCard->title()
                        + "\nOwned by " + agentCard->owner().lock()->name();
                if (agentCard->placement().lock()) {
                    toolTipString += "\nConnections at " + agentCard->placement().lock()->name() + " is " + QString::number(agentCard->connections());
                }
            } else {
                toolTipString = "Card type: " + mCard->typeName() + "\nName: " + mCard->name() + "\n" + mCard->title();
            }

        } else {
            if (mCard->owner().lock()) {
                toolTipString = "Card type: " + mCard->typeName()
                        + "\nName: " + mCard->name()
                        + "\n" + mCard->title()
                        + "\nOwned by " + mCard->owner().lock()->name()
                        + "\nWith influence: " + QString::number(mCard->location().lock().get()->influence(mCard->owner().lock()));
            } else {
                toolTipString = "Card type: " + mCard->typeName() + "\nName: " + mCard->name() + "\n" + mCard->title() + "\nInfluence: "
                                    + QString::number(mCard->location().lock().get()->influence(game_->currentPlayer()));
            }

        }
        setToolTip(toolTipString);
        QGraphicsItem::hoverEnterEvent(event);
    }
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    try {
        QToolTip::hideText();
        QGraphicsItem::hoverLeaveEvent(event);
    }  catch (...) {
        qDebug() << "leave error";
    }

}
