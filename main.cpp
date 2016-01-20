//#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "tmxfiles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();



    TMXFiles tmx;
    tmx.ReadFiles("/tmp/teste2.tmx");
    //tmx.Print();
    qDebug() << "tiledsize:" << tmx.TiledSize();
    qDebug() << "matrixsize:" << tmx.MatrixSize();
    return a.exec();
}
