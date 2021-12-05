#ifndef CARDBAGDIALOG_H
#define CARDBAGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QTextBrowser>

#include "../Course/game.h"
#include "../Course/player.h"
#include "../Course/cardinterface.h"
#include "../Course/location.h"
#include "../Course/influence.h"

#include "offlinereader.h"


/**
 * @file
 * @brief Implement a dialog that shows influence cards gained from current location
 */
namespace Ui {
class CardBagDialog;
}

/**
 * @brief Implement a dialog that shows influence cards gained from current location
 */
class CardBagDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief CardBagDialog constructor
     * @pre -
     * @param game, share pointer to current game
     * @param offlinedata, pointer to the init data
     * @param location, pointer to the current location
     * @param parent
     * @post dialog is not in removed state
     */
    explicit CardBagDialog(std::shared_ptr<Interface::Game> game, std::shared_ptr<ReadData::OfflineData> offlinedata, std::shared_ptr<Interface::Location> location, QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~CardBagDialog();

private:
    Ui::CardBagDialog *ui;
    std::shared_ptr<Interface::Game> game_;
    std::shared_ptr<ReadData::OfflineData> offlinedata_;
    std::shared_ptr<Interface::Location> location_;

};

#endif // CARDBAGDIALOG_H
