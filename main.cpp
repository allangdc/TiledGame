//#include "mainwindow.h"

#include <QApplication>
#include <tinyxml2.h>

#include "tmxfiles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();



    TMXFiles tmx;
    tmx.ReadFiles("/tmp/teste2.tmx");
    return a.exec();
}
