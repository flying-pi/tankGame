#include "listbsemap.h"
#include "../util/baseutil.h"


ListBseMap::ListBseMap(double width, double heigth)
{
    size = new QSizeF(width,heigth);
}

ListBseMap::~ListBseMap()
{
    delete items;
    delete size;
}

QSizeF *ListBseMap::getSize()
{
    delete size;
}

void ListBseMap::insertElement(IBaseGameElement *element, QPointF point)
{
    items->append(element);
}

void ListBseMap::proccessAllInR(IBaseGameElement *element, double r, bool (&mapOperator)(IBaseGameElement *))
{
    for(int i=0;i<items->size();i++){
        IBaseGameElement *el = items->at(i);
        if(element!=el && distanceBetweenElement(el,element))
            mapOperator(el);
    }
}

int ListBseMap::getCount()
{
    return items->size();
}

IBaseGameElement *ListBseMap::getElementAtPosition(int pos)
{
    return items->at(pos);
}
