#include "model.h"
#include "controller.h"
#include "mainwindow.h"
#include "history.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}



