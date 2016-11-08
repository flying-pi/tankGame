#ifndef LISTBSEMAP_H
#define LISTBSEMAP_H

#include "imap.h"
#include <QList>

class ListBseMap : public IMap
{
public:
    ListBseMap(double width,double heigth);
~ListBseMap();
    // IMap interface
public:
    QSizeF *getSize();
    void insertElement(IBaseGameElement *element, QPointF point);
    void proccessAllInR(IBaseGameElement *element, double r,bool (&mapOperator)(IBaseGameElement *));
    int getCount();
    IBaseGameElement *getElementAtPosition(int pos);

protected:
QList<IBaseGameElement *> *items;
QSizeF *size;

};

#endif // LISTBSEMAP_H
