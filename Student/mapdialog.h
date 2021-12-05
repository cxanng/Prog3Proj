#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <qdebug.h>
#include <QGraphicsScene>

#include "mainwindow.h"

/**
 * @file
 * @brief Implement a dialog that shows the map
 */
namespace Ui {
class MapDialog;
}
/**
 * @brief The MapDialog class implement a dialog that shows the map
 */
class MapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapDialog(QWidget *parent = nullptr);
    ~MapDialog();

    void setMap(QImage &img);
private:
    int WIDTH = 1300;
    int HEIGHT = 800;
    Ui::MapDialog *ui;
    QGraphicsScene* map_;

};

#endif // MAPDIALOG_H
