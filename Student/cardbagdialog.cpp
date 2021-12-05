#include "cardbagdialog.h"
#include "ui_cardbagdialog.h"

CardBagDialog::CardBagDialog(std::shared_ptr<Interface::Game> game, std::shared_ptr<ReadData::OfflineData> offlinedata, std::shared_ptr<Interface::Location> location, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardBagDialog),
    game_(game),
    offlinedata_(offlinedata),
    location_(location)
{
    ui->setupUi(this);
    this->setWindowTitle("Card Bag");
    this->setFixedSize(600, 500);

    QScrollArea* bagArea = new QScrollArea(this);
    bagArea->setFixedSize(570, 480);
    bagArea->move(10,10);
    bagArea->show();
    QGridLayout* layout = new QGridLayout(bagArea);

    qDebug() <<game_->currentPlayer()->name();
    int position = 0;
    for (auto const& card : game_->currentPlayer()->cards()) {
        if (card->typeName() == "Influence") {
            std::shared_ptr<Interface::Influence> influenceCard = std::static_pointer_cast<Interface::Influence>(card);
            if (influenceCard->location().lock()->name() == location_->name()) {
                for (auto const& influenceCard : offlinedata_->influenceCard){
                    if (card->name() == influenceCard.name) {
                        QLabel* cardImg = new QLabel(this);
                        cardImg->setPixmap(QPixmap::fromImage(QImage(influenceCard.img)).scaled(100, 100));
                        cardImg->setFixedSize(100, 100);
                        cardImg->setStyleSheet("border-width: 1px; border-style: solid;");
                        layout->addWidget(cardImg, position / 3, position % 3);
                        position ++;
                    }
                }
            }
        }
    }
}

CardBagDialog::~CardBagDialog()
{
    delete ui;
}
