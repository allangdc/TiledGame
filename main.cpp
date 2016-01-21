//#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "tmxfiles.h"
#include "tmxscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TMXFiles tmx;

    tmx.ReadFiles("/tmp/map_tank.tmx");

    TMXScreen src(&tmx);
    src.setScreenSize(QSizeF(300, 300));
    src.AddColumnRight();
    src.RemoveColumnLeft();
    src.Print();

    //tmx.Print();

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
