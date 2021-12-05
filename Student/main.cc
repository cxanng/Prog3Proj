#include <QApplication>
#include "./mainwindow.h"
//#include "../Course/simplemainwindow.hh"
#include "./startdialog.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(default_assets);

//    SimpleMainWindow w{}
    MainWindow w{};
    w.show();

    return a.exec();
}
