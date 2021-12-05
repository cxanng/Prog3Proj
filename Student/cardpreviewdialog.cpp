#include "cardpreviewdialog.h"
#include "ui_cardpreviewdialog.h"

CardPreviewDialog::CardPreviewDialog(std::shared_ptr<Interface::CardInterface> card, std::shared_ptr<ReadData::OfflineData> offlinedata, std::shared_ptr<Interface::Location> location, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardPreviewDialog),
    card_(card),
    offlinedata_(offlinedata),
    location_(location)
{
    ui->setupUi(this);
    this->setWindowTitle("Card Preview");
    this->setFixedSize(550, 400);
    this->move(300, 300);

    QString name = "";
    QString title = "";
    QString img = "";
    unsigned short amount = 0;

    if (card_->typeName() == "Agent") {
        for (auto const& offlineCard : offlinedata_->agentCards.at(location_->id())) {
             if (card->name() == offlineCard.name){
                 name = offlineCard.name;
                 title = offlineCard.title;
                 img = offlineCard.img;
             }
        }
    } else if (card_->typeName() == "Influence") {
        for (auto const& offlineCard : offlinedata_->influenceCard) {
             if (card->name() == offlineCard.name){
                 name = offlineCard.name;
                 img = offlineCard.img;
                 amount = offlineCard.amount;
             }
        }
    }

    QLabel* cardImg = new QLabel(this);
    cardImg->setPixmap(QPixmap::fromImage(QImage(img)).scaled(210, 300));
    cardImg->setFixedSize(210, 300);
    cardImg->move(20, 20);
    cardImg->setStyleSheet("border-width: 1px; border-style: solid;");

    QLabel* locationName = new QLabel("Location name: " + location_->name(), this);
    locationName->move(300, 50);

    QLabel* cardName = new QLabel("Card name: " + name, this);
    cardName->move(300, 90);
    if (card->typeName() == "Agent") {
        QLabel* cardTitle = new QLabel("Card title: " + title, this);
        cardTitle->move(300, 130);
    }

    if (card_->typeName() == "Influence") {
        QLabel* cardAmount = new QLabel("Card influence from " +location_->name() + ": " + QString::number(amount), this);
        cardAmount->move(300, 130);
    }
}

CardPreviewDialog::~CardPreviewDialog()
{
    delete ui;
}
