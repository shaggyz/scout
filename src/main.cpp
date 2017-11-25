#include "ui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Scout");
    a.setApplicationVersion("0.0.1");

    MainWindow w;
    w.show();

    return a.exec();
}
