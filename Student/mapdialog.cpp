#include "mapdialog.h"
#include "ui_mapdialog.h"

MapDialog::MapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapDialog),
    map_(new QGraphicsScene(parent))
{
    ui->setupUi(this);
    ui->mapView->setScene(map_);
    ui->mapView->setFixedSize(WIDTH, HEIGHT);
    ui->mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_->setSceneRect(0,0,WIDTH,HEIGHT);

    map_->setBackgroundBrush(QImage(":/map/runeterra_map"));
    this->resize(WIDTH + 20, HEIGHT + 70);
    ui->closeButton->move(WIDTH - 100, HEIGHT + 30);
    this->setWindowTitle("Runeterra map");

}

MapDialog::~MapDialog()
{
    delete ui;
}
