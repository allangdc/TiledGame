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
    //tmx.ReadFiles("/tmp/teste2.tmx");
    tmx.ReadFiles("/tmp/tobi.tmx");
    tmx.Print();

//    for(int y=0; y<tmx.MatrixSize().height(); y++) {
//        QString s = "| ";
//        for(int x=0; x<tmx.MatrixSize().width(); x++) {
//            s += QString("%1").arg(tmx.MatrixID(0, x, y));
//            if(x != tmx.MatrixSize().width()-1)
//                s += ",";
//            else
//                s += " |";
//        }
//        qDebug() << s;
//    }
    return a.exec();
}
