#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextBlock>
#include <QPushButton>
#include <QLabel>
#include <QTimeEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <qdebug.h>

#include "./Utils/helper.h"

/**
 * @file
 * @brief implement a dialog for greeting and changing the settings of the game
 */
namespace Ui {
class StartDialog;
}

/**
 * @brief a dialog for greeting and changing the settings of the game
 */
class StartDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief StartDialog constructor
     * @pre -
     * @param parent
     * @post dialog is not in removed state
     */
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();
signals:
    /**
     * @brief SIGNAL getSettingChange
     * @param gameSetting
     */
    void gameSettingChange(Utils::GameSetting gameSetting);
public slots:
    /**
     * @brief onOpenSetting
     * @pre -
     * @post exception guarantee: no-throw
     * @exception if memory is not available, the function might leak out std::bad_alloc
     */
    void onOpenSetting();
private:
    Ui::StartDialog *ui;
    QPushButton* settingButton;
};

#endif // STARTDIALOG_HH
