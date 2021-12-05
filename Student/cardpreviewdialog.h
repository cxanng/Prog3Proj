#ifndef CARDPREVIEWDIALOG_H
#define CARDPREVIEWDIALOG_H

#include <QWidget>
#include <QLabel>

#include "../Course/cardinterface.h"
#include "../Course/influence.h"
#include "../Course/location.h"

#include "agent.h"
#include "offlinereader.h"

/**
 * @file
 * @brief Implement a dialog that shows information of the card after being drawn from the deck
 */
namespace Ui {
class CardPreviewDialog;
}

/**
 * @brief The CardPreviewDialog class shows infos of a card after being drawn from the deck
 */
class CardPreviewDialog : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief CardPreviewDialog constructor
     * @pre -
     * @param card, pointer to the card needed detail preview
     * @param offlinedata, pointer to the init data
     * @param location, pointer to the current location
     * @param parent
     * @post dialog is not in removed state
     */
    explicit CardPreviewDialog(std::shared_ptr<Interface::CardInterface> card, std::shared_ptr<ReadData::OfflineData> offlinedata,std::shared_ptr<Interface::Location> location,  QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~CardPreviewDialog();

private:
    Ui::CardPreviewDialog *ui;
    std::shared_ptr<Interface::CardInterface> card_;
    std::shared_ptr<ReadData::OfflineData> offlinedata_;
    std::shared_ptr<Interface::Location> location_;
};

#endif // CARDPREVIEWDIALOG_H
