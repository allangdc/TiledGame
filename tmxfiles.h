#ifndef TMXFILES_H
#define TMXFILES_H

#include <QString>
#include <QVector>
#include <QDomNode>
#include <QDomElement>
#include <QSize>

class Image {
public:
    Image() {}
    void Load(QDomElement *img);
    void Print(int tabs);
    QString source;
    int width;
    int height;
};

class Animation {
public:
    Animation();
    int tileid;
    int duration;
};

class Tile {
public:
    Tile() {}
    Tile(int id);
    void Load(QDomElement *tl);
    void Print(int tabs);
    int id;
    qreal probability;
    QVector<Animation> animation;
};

class TileSet {
public:
    TileSet() {}
    void Load(QDomElement *ts);
    void Print(int tabs=0);
    int firstgid;
    QString name;
    int spacing;
    int margin;
    int tilecount;
    Image image;
    QVector<Tile> tile;
};

class Layer {
public:
    Layer() {}
    Layer(const Layer &l);
    void Load(QDomElement *ly);
    void Print(int tabs);
    QString name;
    int width;
    int height;
    QVector<int> data;
};

class Object {
public:
    enum { RECT, ELLIPSE, POLYGON };
    Object();
    int id;
    int type;
};

class ObjectRect: public Object {
public:
    ObjectRect();
    qreal x, y, width, height;
};

class ObjectEllipse: public Object {
public:
    ObjectEllipse();
    qreal x, y, width, height;
};

class ObjectPolygon: public Object {
public:
    ObjectPolygon();
    qreal x, y;
    QVector<qreal> points;
};

class ObjectGroup {
public:
    ObjectGroup() {}
    int id;
    int type;
    QVector<Object *> object;
};

class Map {
public:
    Map() {}
    void Load(QDomElement *root);
    void Print(int tabs=0);
    qreal version;
    QString orientation;
    QString renderorder;
    int width;
    int height;
    int tilewidth;
    int tileheight;
    TileSet tileset;
    QVector<Layer> layers;
    ObjectGroup objectgroup;
};

class TMXFiles
{
public:
    explicit TMXFiles();
    bool ReadFiles(QString filename);
    void Print();
    Map *GetMap();
    QSize TiledSize();
    QSize MatrixSize();
    int NumLayers();
    int MatrixID(int layer, int x, int y);
    Tile MatrixTile(int layer, int x, int y);
    Tile TileByID(int id);
private:
    QDomElement root;
    Map *map;
};

#endif // TMXFILES_H
