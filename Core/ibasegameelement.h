#ifndef IBASEGAMEELEMENT_H
#define IBASEGAMEELEMENT_H

#include <QObject>
#include "infinitydouble.h"
#include <QPointF>
#include <QByteArray>
#include <QDataStream>

enum difType{
    creation = 1,
    change = 2,
    die = 3,
};

class IBaseGameElement : public QObject
{
    Q_OBJECT
public:
    IBaseGameElement(){
        helth = InfinityDouble::FromValue(1);
        weight = InfinityDouble::FromValue(0);
        transitWeight = InfinityDouble::FromValue(0);
        position = new QPointF(0,0);
    }

    virtual QPointF *getPosition(){return position;}
    virtual int getType(){return type;}
    virtual InfinityDouble *getHelth(){return helth;}
    virtual InfinityDouble *getWeight(){return weight;}
    virtual InfinityDouble *getMaxTransitWeight(){return transitWeight;}

    friend QDataStream& operator << (QDataStream& stream, const IBaseGameElement& myclass)
    {
        return stream << (*myclass.position)  << (*myclass.helth) << (*myclass.weight) << (*myclass.transitWeight);
    }
    friend QDataStream& operator >> (QDataStream& stream, const IBaseGameElement& myclass)
    {
        return stream >> (*myclass.position) >> (*myclass.helth) >> (*myclass.weight) >> (*myclass.transitWeight);
    }

    virtual ~IBaseGameElement(){
        delete helth;
        delete weight;
        delete transitWeight;
        delete position;
    }


    virtual void setPosition(QPointF *value){this->position = value;    }

    virtual void setHelth(InfinityDouble *value){ this->helth = value;    }

    virtual void setWeight(InfinityDouble *value){ this->weight = value;    }

    virtual void setTransitWeight(InfinityDouble *value){this->transitWeight = value;    }

    virtual void setType(int value){ this->type = value;    }

signals:

public slots:

protected:
    QPointF *position ;
    InfinityDouble *helth ;
    InfinityDouble *weight ;
    InfinityDouble *transitWeight;
    int type = -1;
};



#endif // IBASEGAMEELEMENT_H
