#include "tmxfiles.h"

#include <QFile>
#include <QDebug>

TMXFiles::TMXFiles(QObject *parent) : QObject(parent)
{

}

bool TMXFiles::ReadFiles(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file, false)) {
        return false;
    }
    root = doc.documentElement();
    if(root.tagName() != "map")
        return false;

    map = new Map();
    map->Load(&root);
    map->Print();
}

/***************************
*           MAP
****************************/
void Map::Load(QDomElement *root)
{
    version = root->attribute("version").toDouble();
    orientation = root->attribute("orientation");
    renderorder = root->attribute("renderorder");
    width = root->attribute("width").toInt();
    height = root->attribute("height").toInt();
    tilewidth = root->attribute("tilewidth").toInt();
    tileheight = root->attribute("tileheight").toInt();

    for(int i=0; i<root->childNodes().size(); i++) {
        QDomElement e = root->childNodes().at(i).toElement();
        if(e.tagName() == "tileset") {
            tileset.Load(&e);
        } else if(e.tagName() == "layer") {
            Layer l;
            l.Load(&e);
            layers.push_back(l);
        }
    }
}

void Map::Print(int tabs)
{
    QString t;
    for(int i=0; i<tabs; i++)
        t += "\t";
    qDebug() << t.toStdString().c_str() << "*** MAP ***";
    qDebug() << t.toStdString().c_str() << '\t' << "version:" << version;
    qDebug() << t.toStdString().c_str() << '\t' << "orientation:" << orientation;
    qDebug() << t.toStdString().c_str() << '\t' << "renderorder:" << renderorder;
    qDebug() << t.toStdString().c_str() << '\t' << "width:" << width;
    qDebug() << t.toStdString().c_str() << '\t' << "height:" << height;
    qDebug() << t.toStdString().c_str() << '\t' << "tilewidth:" << tilewidth;
    qDebug() << t.toStdString().c_str() << '\t' << "tileheight:" << tileheight;

    tileset.Print(tabs+1);
    for(int i=0; i<layers.size(); i++) {
        Layer layer = layers.at(i);
        layer.Print(tabs+1);
    }
}

/***************************
*           TileSet
****************************/
void TileSet::Load(QDomElement *ts)
{
    firstgid = ts->attribute("firstgid").toInt();
    name = ts->attribute("name");
    spacing = ts->attribute("spacing").toInt();
    margin = ts->attribute("margin").toInt();
    tilecount = ts->attribute("tilecount").toInt();

    for(int i=0; i<tilecount; i++) {
        Tile tile(i);
        this->tile.push_back(tile);
    }


    for(int i=0; i<ts->childNodes().size(); i++) {
        QDomElement e = ts->childNodes().at(i).toElement();
        if(e.tagName() == "image")
            image.Load(&e);
        else if(e.tagName() == "tile") {
            Tile tile;
            tile.Load(&e);
            this->tile[tile.id] = tile;
        }
    }
}

void TileSet::Print(int tabs)
{
    QString t;
    for(int i=0; i<tabs; i++)
        t += "\t";
    qDebug() << t.toStdString().c_str() << "*** TileSet ***";
    qDebug() << t.toStdString().c_str() << '\t' << "firstgid:" << firstgid;
    qDebug() << t.toStdString().c_str() << '\t' << "name:" << name;
    qDebug() << t.toStdString().c_str() << '\t' << "spacing:" << spacing;
    qDebug() << t.toStdString().c_str() << '\t' << "margin:" << margin;
    qDebug() << t.toStdString().c_str() << '\t' << "tilecount:" << tilecount;

    image.Print(tabs+1);
    for(int i=0; i<tile.size(); i++) {
        Tile t = tile.at(i);
        t.Print(tabs+1);
    }
}


/***************************
*           Image
****************************/
void Image::Load(QDomElement *img)
{
    source = img->attribute("source");
    width = img->attribute("width").toInt();
    height = img->attribute("height").toInt();
}

void Image::Print(int tabs)
{
    QString t;
    for(int i=0; i<tabs; i++)
        t += "\t";
    qDebug() << t.toStdString().c_str() << "*** Image ***";
    qDebug() << t.toStdString().c_str() << '\t' << "source:" << source;
    qDebug() << t.toStdString().c_str() << '\t' << "width:" << width;
    qDebug() << t.toStdString().c_str() << '\t' << "height:" << height;
}


/***************************
*           Tile
****************************/

Tile::Tile(int id)
{
    this->id = id;
    probability = 1;
}

void Tile::Load(QDomElement *tl)
{
    id = tl->attribute("id").toInt();
    probability = tl->attribute("probability").toFloat();
    if (probability == 0)
        probability = 1;
}

void Tile::Print(int tabs)
{
    QString t;
    for(int i=0; i<tabs; i++)
        t += "\t";
    qDebug() << t.toStdString().c_str() << "*** Tile ***";
    qDebug() << t.toStdString().c_str() << '\t' << "id:" << id;
    qDebug() << t.toStdString().c_str() << '\t' << "probability:" << probability;
}

/***************************
*           Layer
****************************/
Layer::Layer(const Layer &l)
{
    name = l.name;
    width = l.width;
    height = l.height;
    data = l.data;
}

void Layer::Load(QDomElement *ly)
{
    QDomElement dt = ly->firstChildElement("data").toElement();
    for(int i=0; i<dt.childNodes().size(); i++) {
        QDomElement tile = dt.childNodes().at(i).toElement();
        int id = tile.attribute("gid").toInt();
        data.push_back(id);
    }
    name = ly->attribute("name");
    width = ly->attribute("width").toInt();
    height = ly->attribute("height").toInt();
}

void Layer::Print(int tabs)
{
    QString t;
    for(int i=0; i<tabs; i++)
        t += "\t";
    qDebug() << t.toStdString().c_str() << "*** Layer ***";
    qDebug() << t.toStdString().c_str() << '\t' << "name:" << name;
    qDebug() << t.toStdString().c_str() << '\t' << "width:" << width;
    qDebug() << t.toStdString().c_str() << '\t' << "height:" << height;
    for(int i=0; i<data.size(); i++)
        qDebug() << t.toStdString().c_str() << '\t' << "data:" << data.at(i);
}
