#ifndef TMXSCREEN_H
#define TMXSCREEN_H

#include <QSizeF>
#include <QVector>
#include <QList>
#include <QRectF>
#include <QPixmap>

#include "tmxfiles.h"

class Node {
public:
    Node() {}
    int value;
    QRectF geometry;
    QPoint coord;
};

class TMXScreen
{
public:
    TMXScreen(TMXFiles *tmxfile);
    void setScreenSize(QSizeF size);

    void TestScreenRight();
    void MoveRight(qreal step);
    void TestScreenTop();
    void MoveTop(qreal step);

    bool AddColumnRight();
    bool AddColumnLeft();
    bool AddRowBottom();
    bool AddRowTop();

    void RemoveColumnRight();
    void RemoveColumnLeft();
    void RemoveRowBottom();
    void RemoveRowTop();

    void Print();
private:
    QRectF screen;
    TMXFiles *tmxfile;
    QList< QVector<Node> > nodes;
};

#endif // TMXSCREEN_H
