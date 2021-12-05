#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cardpreviewdialog.h"

const qreal PADDING = 85;
static int CARD_WIDTH = 140;
static int CARD_HEIGHT = 200;
static int PADDING_Y = 10;
static int PADDING_X = 10;
using CardPtr = std::shared_ptr<Interface::CardInterface>;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player_infor_map(),
    game_(std::make_shared<Interface::Game>()),
    current_location_(),
    isStarted(false)
{
    //default game setting
    gameSetting_ = {4, 10, 2, {"Player 1", "Player 2"}};
    timer = new QTimer(this);

    ReadData::OfflineReader offlinereader_;
    offlinedata_ = offlinereader_.readFileToData(Utils::LOCATION_FILE, Utils::AGENT_COUNCILOR_FILE, Utils::INFLUENCE_FILE, Utils::INIT_AGENT_FILE);

    StartDialog *dialog = new StartDialog(this);
    dialog->move(1000,200);
    connect(dialog, &StartDialog::gameSettingChange, [&](Utils::GameSetting gameSetting) {
        this->gameSetting_ = gameSetting;
    });
    connect(dialog, &StartDialog::rejected, [&](){ close();});
    dialog->show();

    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(1800, 900);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->lcdNumberMin->setPalette(Qt::black);
    ui->lcdNumberSec->setPalette(Qt::black);
    ui->lcdNumberMin->setMinimumHeight(30);
    ui->lcdNumberSec->setMinimumHeight(30);
    ui->playerStatusTextBrowser->setFixedSize(200,100);
    ui->playerStatusTextBrowser->setText("Player status");
    ui->lcdNumberMin->move(width_+ PADDING, PADDING - 50);
    ui->lcdNumberSec->move(width_+ PADDING + 70, PADDING - 50);
    ui->playerStatusTextBrowser->move(width_ + 4*PADDING, PADDING);
    ui->startButton->move(width_+ PADDING, PADDING);
    ui->showMapButton->move(width_ + PADDING + 100, PADDING);
    ui->locationColection->move(width_ + PADDING, 2*PADDING);
    ui->nextActionCollection->move(width_+ PADDING, 3*PADDING);
    ui->confirmActionButton->move(width_+ PADDING, 4*PADDING);
    ui->sendAgentButton->move(width_ + PADDING, 5*PADDING);
    ui->cardBagButton->move(width_ + PADDING, 6*PADDING);
    ui->endTurnButton->move(width_+ PADDING, 7*PADDING);
    ui->locationColection->addItem("None");
    ui->locationColection->setMinimumWidth(200);
    ui->nextActionCollection->setMinimumWidth(200);
    ui->confirmActionButton->setDisabled(true);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    connect(timer, &QTimer::timeout, this, &MainWindow::finish_1000ms);
    connect(ui->startButton, &QPushButton::clicked, [&](){startGame();});
    connect(ui->locationColection, &QComboBox::currentTextChanged, [&](){location_choose();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawSlots(int rows, int columns)
{
    for ( int row = 0; row < rows; row++){
        cards_.push_back({});
        for ( int column = 0; column < columns; column++){
            cards_.back().push_back(nullptr);
            drawCustomCardToSlot(row, column, "");
        }
    }
    ui->gameView->setMinimumSize(CARD_WIDTH * columns + PADDING_X * (columns + 2), CARD_HEIGHT * rows + PADDING_Y * (rows + 2));
}

CardItem* MainWindow::drawCardToSlot(std::shared_ptr<Interface::CardInterface> card, int row, int column)
{
   return drawCustomCardToSlot(row, column, card->name(), card, card->title());
}

CardItem* MainWindow::drawCustomCardToSlot(int row, int column, QString name, std::shared_ptr<Interface::CardInterface> card, QString description)
{
    QString img ="";
    if (card) {
        if (card->typeName() == "Councilor" || card->typeName() == "Agent") {
            for (auto const& [_, item]: offlinedata_->agentCards) {
                for (unsigned int i = 0; i< item.size(); i++ ) {
                    if (item[i].name == name) {
                        img = item[i].img;
                    }
                }
            }
            if (img == "") {
                for (unsigned int i = 0; i< offlinedata_->initAgentCard.size(); i++ ) {
                    if (offlinedata_->initAgentCard[i].name == name) {
                        img = offlinedata_->initAgentCard[i].img;
                    }
                }
            }
        } else if (card->typeName() == "Influence") {
            for (auto const& item: offlinedata_->influenceCard) {
                if (item.name == name) {
                    img = item.img;
                }
            }
        }
    }
    CardItem* nCard = new CardItem(name, card, game_, description, img, map);
    cards_.at(row).at(column) = nCard;
    map->addItem(nCard);
    nCard->moveBy(200+ (CARD_WIDTH + PADDING_X) * column, (CARD_HEIGHT + PADDING_Y) * row);
    return nCard;
}

void MainWindow::setTableBackground(QImage img)
{
    map->setBackgroundBrush(img);
}

void MainWindow::startGame() {
    if (isStarted) {
        return;
    }
    isStarted = true;
    game_->setActive(true);
    runner_ = std::make_shared<Interface::Runner>(game_);
    QGraphicsTextItem* councilorText = new QGraphicsTextItem;
    councilorText->setPos(20, 70);
    councilorText->setScale(1.2);
    councilorText->setHtml("<div style='background-color:#000000; color:#FFFFFF'>Councilor and agents</div>");

    QGraphicsTextItem* deckText = new QGraphicsTextItem;
    deckText->setPos(20, 280);
    deckText->setScale(1.2);
    deckText->setHtml("<div style='background-color:#000000; color:#FFFFFF'>Deck</div>");

    QGraphicsTextItem* playerCardsText = new QGraphicsTextItem;
    playerCardsText->setPos(20, 700);
    playerCardsText->setScale(1.1);
    playerCardsText->setHtml("<div style='background-color:#000000; color:#FFFFFF'>Current player's cards</div>");

    map->addItem(councilorText);
    map->addItem(deckText);
    map->addItem(playerCardsText);
    minute_ = gameSetting_.game_duration_ - 1;
    second_ = 60;
    timer->start(interval_);
    const std::unordered_map<unsigned int, ReadData::LocationData> locations = offlinedata_->locations;
    const std::unordered_map<unsigned int, std::vector<ReadData::CardData>> agentCards = offlinedata_->agentCards;
    const std::vector<ReadData::CardData> influenceCard = offlinedata_->influenceCard;
    for (int i = 0; i < gameSetting_.locations_; i++) {
        std::shared_ptr<Interface::Location> loc = std::make_shared<Interface::Location>(i, locations.at(i).name);
        loc->initialize();
        for (auto card : agentCards.at(i)) {
            if (card.typeName == "Councilor"){
                std::shared_ptr<Interface::Councilor> councilor = std::make_shared<Interface::Councilor>(card.name, card.title, loc);
                loc->setCouncilor(councilor);
            } else {
                std::shared_ptr<CardModel::Agent> agentCard = std::make_shared<CardModel::Agent>(card.name, card.title);
                loc->deck()->addCard(agentCard);
            }
        }

        while (loc->deck()->size() < Utils::MAX_CARD_IN_DECK) {
            ReadData::CardData randomCard = influenceCard[rand()%influenceCard.size()];
            std::shared_ptr<Interface::Influence> influence = std::make_shared<Interface::Influence>(randomCard.name, loc, randomCard.amount);
            loc->deck()->addCard(influence);
        }
        game_->addLocation(loc);
    }
    for (const auto &loc: game_->locations()) {
        ui->locationColection->addItem(QString::number(loc->id()) + " " + loc->name());
    }

    for (const auto &action: actions_) {
        ui->nextActionCollection->addItem(action);
    }

    for (int k = 0; k < gameSetting_.players_; k++) {
        std::shared_ptr<Interface::Player> newPlayer = std::make_shared<Interface::Player>(game_ , k, gameSetting_.name_[k]);
        game_->addPlayer(newPlayer);
        player_infor_map.insert({static_cast<unsigned short>(k),{static_cast<unsigned short>(k), newPlayer->name(), 1, 0}});
        std::shared_ptr<CardModel::Agent> newAgentCard = std::make_shared<CardModel::Agent>(offlinedata_->initAgentCard[k].name,
                                                                                             offlinedata_->initAgentCard[k].title + newPlayer->name());
        game_->players()[k]->addCard(newAgentCard);
        runner_->setPlayerControl(newPlayer, std::make_shared<Interface::ManualControl>());
    }
    update_table();

    connect(ui->endTurnButton, &QPushButton::clicked, [&](){end_turn();});
    connect(ui->showMapButton, &QPushButton::clicked, [&](){open_map_dialog();});
    connect(ui->nextActionCollection, &QComboBox::currentTextChanged, [&](){next_action_choose();});
    connect(ui->confirmActionButton, &QPushButton::clicked, [&](){next_action_confirm();});
    connect(ui->cardBagButton, &QPushButton::clicked, [&](){open_card_bag();});
    connect(ui->sendAgentButton, &QPushButton::clicked, [&](){on_send_agent_button_clicked();});
    connect(this, &MainWindow::endGame, [&](){onEndGame();});
}

void MainWindow::finish_1000ms()
{
    if (second_ == 0 && minute_ == 0) {
        emit endGame();
        timer->stop();
    }
    else {
        timer->start(interval_);
        second_ --;

        if(second_ < 0) {
            second_ = 59;
            minute_ --;
        }

        ui->lcdNumberMin->display(minute_);
        ui->lcdNumberSec->display(second_);
    }
}

void MainWindow::onEndGame()
{
    game_->setActive(false);
    ui->startButton->setDisabled(true);
    ui->locationColection->setDisabled(true);
    ui->nextActionCollection->setDisabled(true);
    ui->confirmActionButton->setDisabled(true);
    ui->sendAgentButton->setDisabled(true);
    ui->endTurnButton->setDisabled(true);
    ui->cardBagButton->setDisabled(true);

    QDialog* endGameDialog = new QDialog(this);
    endGameDialog->setFixedSize(700, 300);
    endGameDialog->move(300, 300);

    unsigned short higest_score = 0;
    QString winner_text = "The winner: ";
    for (auto const& info : player_infor_map) {
        if (info.second.score > higest_score) {
            higest_score = info.second.score;
        }
    }
    for (auto const& info : player_infor_map) {
        if (info.second.score == higest_score) {
            winner_text += info.second.name + " ";
        }
        QLabel* player_info = new QLabel(info.second.name + " (Score: " + QString::number(info.second.score) + ")", endGameDialog);
        player_info->move(10, 50 + info.first * 40);
    }
    QLabel* winner_banner = new QLabel(winner_text, endGameDialog);
    QFont font = winner_banner->font();
    font.setPointSize(16);
    font.setBold(true);
    winner_banner->setFont(font);
    winner_banner->move(10, 10);

    QPushButton* close_dialog = new QPushButton(endGameDialog);
    close_dialog->setText("Close");
    close_dialog->move(10, 200);
    connect(close_dialog, &QPushButton::clicked, [&]() {this->close();});
    endGameDialog->show();
}

void MainWindow::location_choose()
{
    const QString current_choice = ui->locationColection->currentText();
    if (current_choice != "None") {
        for (auto const& loc : game_->locations()) {
            if (QString::number(loc->id()) == current_choice.split(" ").value(0)) {
                current_location_ = loc;
                update_table();
                break;
            }
        }
        if (current_location_->councilor()->owner().lock() != nullptr &&
                current_location_->councilor()->owner().lock() != game_->currentPlayer()) {
            ui->sendAgentButton->setDisabled(true);
        } else {
            ui->sendAgentButton->setDisabled(false);
        }
    }
}

void MainWindow::open_map_dialog() {
    if (game_->active()) {
        MapDialog *dialog = new MapDialog(this);
        dialog->move(1000,200);
        dialog->show();
    }
}

void MainWindow::next_action_choose() {
    if (!current_location_ || ui->nextActionCollection->currentText() == "None") {
        ui->confirmActionButton->setDisabled(true);
    } else {
        bool agentSent = false;
        for (auto const& agent: current_location_->agents()) {
            if (agent->owner().lock() == game_->currentPlayer()) {
                agentSent = true;
                break;
            }
        }
        if (current_location_->councilor()->owner().lock() != game_->currentPlayer()
                && current_location_->councilor()->owner().lock() != nullptr) {
            ui->confirmActionButton->setDisabled(true);
        } else {
            ui->confirmActionButton->setDisabled(!agentSent);
        }
    }
}

void MainWindow::next_action_confirm() {
    QString next_action = ui->nextActionCollection->currentText();
    if (current_location_) {
        if (next_action == "Withdraw agents") {
            if (!Utils::canGetMoreAgent(game_->currentPlayer())) {
                qDebug() << "Maximum number of agents reached, try again later";
            } else {
                for (auto const& agent: current_location_->agents()) {
                    if (agent->owner().lock() == game_->currentPlayer()) {
                        std::shared_ptr<Interface::WithdrawAction> action = std::make_shared<Interface::WithdrawAction>(agent);
                        std::shared_ptr<Interface::ManualControl> control = std::static_pointer_cast<Interface::ManualControl>(runner_->playerControl(game_->currentPlayer()));
                        control->setNextAction(action);
                        break;
                    }
                }
            }
        } else if (next_action == "Shuffle and draw") {
            std::shared_ptr<Action::ShuffleAndDrawAction> action = std::make_shared<Action::ShuffleAndDrawAction>(game_->currentPlayer(), current_location_);
            std::shared_ptr<Interface::ManualControl> control = std::static_pointer_cast<Interface::ManualControl>(runner_->playerControl(game_->currentPlayer()));
            control->setNextAction(action);
        } else if (next_action == "Own area") {
            std::shared_ptr<Action::OwnLocationAction> action = std::make_shared<Action::OwnLocationAction>(game_->currentPlayer(), current_location_);
            std::shared_ptr<Interface::ManualControl> control = std::static_pointer_cast<Interface::ManualControl>(runner_->playerControl(game_->currentPlayer()));
            control->setNextAction(action);
        } else if (next_action == "Strengthen connections") {
            for (auto const& agent: current_location_->agents()) {
                if (agent->owner().lock() == game_->currentPlayer()) {
                    std::shared_ptr<Action::StrengthenConnections> action = std::make_shared<Action::StrengthenConnections>(agent, current_location_);
                    std::shared_ptr<Interface::ManualControl> control = std::static_pointer_cast<Interface::ManualControl>(runner_->playerControl(game_->currentPlayer()));
                    control->setNextAction(action);
                    break;
                }
            }
        }
    }
    try {
        runner_->run();
        if (next_action == "Shuffle and draw") {
            CardPreviewDialog* dialog = new CardPreviewDialog(game_->currentPlayer()->cards()[game_->currentPlayer()->cards().size()-1], offlinedata_, current_location_);
            dialog->show();
        }
        end_turn();
    }  catch (Interface::ControlException err) {
        qDebug() << err.msg();
    }
    ui->nextActionCollection->setCurrentText("None");
    update_table();
}

void MainWindow::end_turn() {
    game_->nextPlayer();
    update_table();
    if (current_location_->councilor()->owner().lock() != nullptr &&
            current_location_->councilor()->owner().lock() != game_->currentPlayer()) {
        ui->sendAgentButton->setDisabled(true);
    } else {
        ui->sendAgentButton->setDisabled(false);
    }
}

void MainWindow::open_card_bag()
{
    CardBagDialog* bagDialog = new CardBagDialog(game_, offlinedata_, current_location_, this);
    bagDialog->show();
}

void MainWindow::update_table() {
    drawSlots();
    ui->nextActionCollection->setCurrentText("None");
    if (current_location_) {
        setTableBackground(QImage(offlinedata_->locations.at(current_location_->id()).img));
        drawCardToSlot(current_location_->councilor(), 0, 0);
        int col = 1;
        for (auto const& agent: current_location_->agents()) {
            drawCardToSlot(agent, 0, col);
            col++;
        }
        for (unsigned int i = 0; i < current_location_->deck()->size(); i++) {
            int row = i < 7 ? 1 : 2;
            int col = i%7;
            drawCardToSlot(current_location_->deck()->cardAt(i), row, col);
        }
    }
    int col = 0;
    for (unsigned short i = 0; i < game_->currentPlayer()->cards().size(); i++) {

        if (game_->currentPlayer()->cards()[i]->typeName() == "Agent") {
            drawCardToSlot(game_->currentPlayer()->cards()[i], 3, col);
            col++;
        }
    }
    update_player_status();
}

void MainWindow::update_player_status()
{
    if (current_location_) {
        unsigned short current_loc_influence = current_location_->influence(game_->currentPlayer());
        unsigned short total_score = 0;
        int total_agent = 0;
        int num_player_has_agent = 0;
        for (auto const& loc :  game_->locations()){
            total_score += loc->influence(game_->currentPlayer());
        }
        QString owned = "";
        if (current_location_->councilor()->owner().lock()) {
            owned = " (owned by " + current_location_->councilor()->owner().lock().get()->name() +  ")";
        }

        ui->playerStatusTextBrowser->setText(current_location_->name() + "\n" + owned +
                                             "\n" + game_->currentPlayer()->name() +"'s turn" +
                                             "\nInfluence point: " + QString::number(current_loc_influence) +
                                             "\nTotal Score: " + QString::number(total_score));

        for (auto const& loc : game_->locations()){
            if (!loc->councilor()->owner().lock()) {
                for (auto const& agent : loc->agents()) {
                    if (agent->owner().lock() == game_->currentPlayer()) {
                        total_agent ++;
                    }
                }
            }
        }
        for (auto const& card : game_->currentPlayer()->cards()) {
            if (card->typeName() == "Agent") {
                total_agent ++;
            }
        }
        player_infor_map.at(game_->currentPlayer()->id()).score = total_score;
        player_infor_map.at(game_->currentPlayer()->id()).agent_num = total_agent;
        for (auto const& item : player_infor_map) {
            if (item.second.agent_num > 0) {
                num_player_has_agent ++;
            }
        }
        if (num_player_has_agent == 1) {
            qDebug() << "Out of agent!";
            emit endGame();
        }
    }
}

void MainWindow::on_send_agent_button_clicked() {
    if (current_location_) {
        std::shared_ptr<CardModel::Agent> agentToBeSent = nullptr;
        for (auto const& card: game_->currentPlayer()->cards()) {
            if (card->typeName() == "Agent") {
                agentToBeSent = std::static_pointer_cast<CardModel::Agent>(card);
                if (agentToBeSent) {
                    std::shared_ptr<Action::SendAgentAction> action = std::make_shared<Action::SendAgentAction>(agentToBeSent, current_location_);
                    std::shared_ptr<Interface::ManualControl> control = std::static_pointer_cast<Interface::ManualControl>(runner_->playerControl(game_->currentPlayer()));
                    control->setNextAction(action);
                    break;
                }
            }
        }
        if (!agentToBeSent) {
            qDebug() << "no agent";
        } else {
            ui->nextActionCollection->setCurrentText("None");
            try {
                runner_->run();
            }  catch (Interface::ControlException err) {
                qDebug() << err.msg();
            }
            update_table();
        }

    }
}
