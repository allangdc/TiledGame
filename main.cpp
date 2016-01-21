//#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "tmxfiles.h"
#include "tmxscreen.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TMXFiles tmx;

    tmx.ReadFiles("map_tank.tmx");

    TMXScreen src(&tmx);
    src.setScreenSize(QSizeF(300, 300));
    src.MoveTop(50);
    src.Print();

    QGraphicsView view;
    view.setGeometry(0,0,800,800);

    QGraphicsScene scene;
    scene.setSceneRect(0,0,800,800);
    QPixmap pmap = tmx.TilesetImage();
    QGraphicsPixmapItem gmap(pmap);
    scene.addItem(&gmap);
    gmap.setPos(0,0);
    view.setScene(&scene);

    view.show();

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
