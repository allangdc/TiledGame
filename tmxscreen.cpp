#include "tmxscreen.h"

#include <QPointF>
#include <QDebug>

TMXScreen::TMXScreen(TMXFiles *tmxfile)
{
    this->tmxfile = tmxfile;
    screen = QRectF(0, 0, 0, 0);
}

void TMXScreen::setScreenSize(QSizeF size)
{
    nodes.clear();
    screen = QRectF(QPointF(0,0), size);
    QSize tilesize = tmxfile->TiledSize();
    qreal width = 0;
    qreal height = 0;
    int x=0;
    int y=0;


    while(height<size.height())
    {
        x = 0;
        width = 0;
        QVector<Node> vnode;
        while(width<size.width()) {
            Node node;
            node.coord = QPoint(x, y);
            node.value = tmxfile->MatrixID(0, x++, y);
            node.geometry = QRectF(QPointF(width, height), QSizeF(tilesize));
            width += tilesize.width();
            vnode.push_back(node);
        }
        y++;
        height += tilesize.height();
        nodes.push_back(vnode);
    }
}

void TMXScreen::TestScreenTop()
{
    QList< QVector<Node> >::iterator it;
    QVector<Node>::iterator vit;
    Node *node;

    it = nodes.begin();
    QVector<Node> *vnode = &(*it);
    vit = vnode->begin();
    node = &(*vit);
    while(screen.top() < node->geometry.top()) {
        if(!AddRowTop())
            break;
        it = nodes.begin();
        vnode = &(*it);
        vit = vnode->begin();
        node = &(*vit);
    }

    while(screen.top() > node->geometry.top() + node->geometry.height()) {
        RemoveRowTop();
        it = nodes.begin();
        vnode = &(*it);
        vit = vnode->begin();
        node = &(*vit);
    }

    it = nodes.end()-1;
    vnode = &(*it);
    vit = vnode->begin();
    node = &(*vit);
    while(screen.top() + screen.height() > node->geometry.top() + node->geometry.height()) {
        if(!AddRowBottom())
            break;
        it = nodes.end()-1;
        vnode = &(*it);
        vit = vnode->begin();
        node = &(*vit);
    }

    while(screen.top() + screen.height() < node->geometry.top()) {
        RemoveRowBottom();
        it = nodes.end()-1;
        vnode = &(*it);
        vit = vnode->begin();
        node = &(*vit);
    }
}

void TMXScreen::TestScreenRight()
{
    QList< QVector<Node> >::iterator it;
    QVector<Node>::iterator vit;
    Node *node;

    it = nodes.begin();
    QVector<Node> *vnode = &(*it);

    vit = vnode->end()-1;
    node = &(*vit);
    while(screen.left() + screen.width() > node->geometry.left() + node->geometry.width()) {
        if(!AddColumnRight())
            break;
        vit = vnode->end()-1;
        node = &(*vit);
    }

    vit = vnode->end()-1;
    node = &(*vit);
    while(screen.left() + screen.width() < node->geometry.left()) {
        RemoveColumnRight();
        vit = vnode->end()-1;
        node = &(*vit);
    }

    vit = vnode->begin();
    node = &(*vit);
    while(screen.left() < node->geometry.left()) {
        if(!AddColumnLeft())
            break;
        vit = vnode->begin();
        node = &(*vit);
    }

    vit = vnode->begin();
    node = &(*vit);
    while(node->geometry.left() + node->geometry.width() < screen.left()) {
        RemoveColumnLeft();
        vit = vnode->begin();
        node = &(*vit);
    }
}

void TMXScreen::MoveRight(qreal step)
{
    screen.setLeft(screen.left() + step);
    screen.setWidth(screen.width() + step);
    TestScreenRight();
}

void TMXScreen::MoveTop(qreal step)
{
    screen.setTop(screen.top() + step);
    screen.setHeight(screen.height() + step);
    TestScreenTop();
}

bool TMXScreen::AddColumnRight()
{
    QList< QVector<Node> >::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        QVector<Node> *vnode = &(*it);
        Node node = vnode->at(vnode->size()-1);
        node.coord.setX(node.coord.x() + 1);
        node.geometry.setLeft(node.geometry.left() + tmxfile->TiledSize().width());
        node.geometry.setWidth(node.geometry.width() + tmxfile->TiledSize().width());
        node.value = tmxfile->MatrixID(0, node.coord.x(), node.coord.y());
        vnode->push_back(node);
    }
    return true;
}

bool TMXScreen::AddColumnLeft()
{
    QList< QVector<Node> >::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        QVector<Node> *vnode = &(*it);
        Node node = vnode->at(0);
        node.coord.setX(node.coord.x() - 1);
        node.geometry.setLeft(node.geometry.left() - tmxfile->TiledSize().width());
        node.geometry.setWidth(node.geometry.width() - tmxfile->TiledSize().width());
        node.value = tmxfile->MatrixID(0, node.coord.x(), node.coord.y());
        vnode->push_front(node);
    }
    return true;
}

bool TMXScreen::AddRowBottom()
{
    QList< QVector<Node> >::iterator it;
    it = nodes.end() - 1;
    QVector<Node> *vnode = &(*it);
    QVector<Node>::iterator vit;
    QVector<Node> n;
    for(vit = vnode->begin(); vit != vnode->end(); vit++) {
        Node node = *vit;
        node.coord.setY(node.coord.y() + 1);
        node.geometry.setTop(node.geometry.top() + tmxfile->TiledSize().height());
        node.geometry.setHeight(node.geometry.height() + tmxfile->TiledSize().height());
        node.value = tmxfile->MatrixID(0, node.coord.x(), node.coord.y());
        n.push_back(node);
    }
    nodes.push_back(n);
    return true;
}

bool TMXScreen::AddRowTop()
{
    QList< QVector<Node> >::iterator it;
    it = nodes.begin();
    QVector<Node> *vnode = &(*it);
    QVector<Node>::iterator vit;
    QVector<Node> n;
    for(vit = vnode->begin(); vit != vnode->end(); vit++) {
        Node node = *vit;
        node.coord.setY(node.coord.y() - 1);
        node.geometry.setTop(node.geometry.top() - tmxfile->TiledSize().height());
        node.geometry.setHeight(node.geometry.height() - tmxfile->TiledSize().height());
        node.value = tmxfile->MatrixID(0, node.coord.x(), node.coord.y());
        n.push_back(node);
    }
    nodes.push_front(n);
    return true;
}

void TMXScreen::RemoveColumnRight()
{
    QList< QVector<Node> >::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        QVector<Node> *vnode = &(*it);
        vnode->pop_back();
    }
}

void TMXScreen::RemoveColumnLeft()
{
    QList< QVector<Node> >::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        QVector<Node> *vnode = &(*it);
        vnode->pop_front();
    }
}

void TMXScreen::RemoveRowBottom()
{
    nodes.pop_back();
}

void TMXScreen::RemoveRowTop()
{
    nodes.pop_front();
}

void TMXScreen::Print()
{
    QList< QVector<Node> >::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        QVector<Node> *vnode = &(*it);
        QVector<Node>::iterator vit;
        QString s = "| ";
        for(vit = vnode->begin(); vit != vnode->end(); vit++) {
            Node *node = &(*vit);
            if(vit == vnode->begin())
                s += QString("%1").arg(node->value);
            else {
                s += QString(" %1").arg(node->value);
            }
        }
        s += " |";
        qDebug() << s;
    }
}









