#ifndef IMAP_H
#define IMAP_H

#include <QSizeF>
#include <QPointF>
#include "ibasegameelement.h"


class IMap
{
public:
    IMap();
    virtual QSizeF *getSize() = 0;
    virtual void insertElement(IBaseGameElement *element,QPointF point) = 0;
    virtual void proccessAllInR(IBaseGameElement *element,double r, bool (&mapOperator)(IBaseGameElement *element)) = 0;
    virtual int getCount() = 0;
    virtual IBaseGameElement *getElementAtPosition(int pos) =0;
};

#endif // IMAP_H
