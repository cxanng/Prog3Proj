#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QVector>
#include <map>
#include <QString>
#include <algorithm>
#include <stdlib.h>
#include <QTextBrowser>

#include "../Course/simplemainwindow.hh"
#include "../Course/game.h"
#include "../Course/location.h"
#include "../Course/influence.h"
#include "../Course/deck.h"
#include "../Course/player.h"
#include "../course/Course/councilor.h"
#include "../course/Course/runner.h"
#include "../course/Course/manualcontrol.h"
#include "../course/Course/controlexception.h"
#include "../course/Course/withdrawaction.h"

#include "startdialog.hh"
#include "mapdialog.h"
#include "agent.h"
#include "carditem.h"
#include "offlinereader.h"
#include "shuffleanddrawaction.h"
#include "sendagentaction.h"
#include "cardbagdialog.h"
#include "ownlocationaction.h"
#include "strengthenconnections.h"

/**
 * @file
 * @brief MainWindow
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief drawSlots
     * @param rows
     * @param columns
     *
     * Draws rows * colums amount of cardslots to the view and fits the view to show all ( if screen permits ).
     * @note This function should be called before placing any cards.
     */
    void drawSlots(int rows = 4, int columns = 7);

    /**
     * @brief drawCardToSlot draws a card with the info gathered through cardinterface.
     * @param card
     * @param row < rows
     * @param column < columns
     * @return pointer to the card item drawn.
     * @note: Drawing cards on top of each other is allowed, but the behaviour
     * of cards other than the topmost one is undetermined.
     */
    CardItem* drawCardToSlot(std::shared_ptr<Interface::CardInterface> card, int row, int column);

    /**
     * @brief drawCustomCardToSlot draws card to the slot provided
     * @param row < rows
     * @param column < columns
     * @param name
     * @param card
     * @param description
     * @param color
     * @return pointer to the card item drawn
     * @note: Drawing cards on top of each other is allowed, but the behaviour
     * of cards other than the topmost one is undetermined.
     */
    CardItem* drawCustomCardToSlot( int row, int column, QString name, std::shared_ptr<Interface::CardInterface> card = nullptr, QString description = "");

    /**
     * @brief setTableBackground, set the background for scene
     * @param img, QImage of the scene background
     */
    void setTableBackground(QImage img);

    /**
     * @brief startGame
     * @pre all setting is done
     */
    void startGame();

private slots:
    /**
     * @brief finish_1000ms, timer for the game
     * @pre - input min must be larger than 0 and second is between 0 and 59
     * @post Exception guarantee: no-throw
     */
    void finish_1000ms();

    /**
     * @brief SLOT onEndGame - display final score and Winner.
     * @pre - game is over
     * @post exception guarantee : basics
     * @exception: if there is no memory available, this might throw exception std::bad_alloc.
     */
    void onEndGame();

signals:
    /**
     * @brief endGame is emitted when running out of time, and when one player is running out of agent card
     * @post Exception guarantee: no-throw
     */
    void endGame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *map;
    std::shared_ptr<ReadData::OfflineData> offlinedata_;
    QTimer* timer;
    int second_;
    int minute_;
    const int interval_ = 1000;
    int width_ = 1300;
    int height_ = 830;

    std::vector<std::vector<CardItem*>> cards_;

    /**
     * @brief The PlayerInfor struct to hold player's infor
     */
    struct PlayerInfor {
        unsigned short id;
        QString name;
        int agent_num;
        unsigned short score;
    };

    std::unordered_map<unsigned short, PlayerInfor> player_infor_map;

    std::shared_ptr<Interface::Game> game_;
    std::shared_ptr<Interface::Runner> runner_;
    std::shared_ptr<Interface::Location> current_location_;
    bool isStarted;
    Utils::GameSetting gameSetting_;

    std::vector<QString> actions_ = {
        "None",
        "Strengthen connections",
        "Shuffle and draw",
        "Own area",
        "Withdraw agents"
    };

    /**
     * @brief location_choose handle changing between locations
     */
    void location_choose();

    /**
     * @brief open_map_dialog handle showing the map
     */
    void open_map_dialog();

    /**
     * @brief next_action_choose handle choosing next action and disable confirm button if needed
     */
    void next_action_choose();

    /**
     * @brief next_action_confirm execute the chosen action
     * @pre action from next_action_choose is performable
     * @post action is executed. Exception guarantee: no-throw
     */
    void next_action_confirm();

    /**
     * @brief end_turn handle end turn
     * @pre _
     * @post current_player will be change to next player
     */
    void end_turn();

    /**
     * @brief open_card_bag open a dialog contains current player's influence cards at current location
     */
    void open_card_bag();

    /**
     * @brief update_table handle update the card table when notify a change
     */
    void update_table();

    /**
     * @brief update_player_status handle update player status when an action is executed
     */
    void update_player_status();

    /**
     * @brief on_send_agent_button_clicked handle send agent
     * @pre the current player has agent on his/her hand and does not have any agent sent to current location
     * @post an agent from player's hand is sent to the location
     */
    void on_send_agent_button_clicked();
};

#endif // MAINWINDOW_H
