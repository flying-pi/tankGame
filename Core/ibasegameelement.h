#ifndef IBASEGAMEELEMENT_H
#define IBASEGAMEELEMENT_H

#include <QObject>
#include "infinitydouble.h"
#include <QPointF>
#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QTime>
#include <QVector3D>

enum eBaseGameElementType { eGrass, eSimpleTank, eBasis };
class IBaseGameElement;

class IBaseGameElement : public QObject {
  Q_OBJECT
 public:
  IBaseGameElement() {
    helth = InfinityDouble::FromValue(1);
    weight = InfinityDouble::FromValue(0);
    transitWeight = InfinityDouble::FromValue(0);
    position = new QVector3D(0, 0, 0);
    name = QString::number(QTime::currentTime().msec());
    additionalData = new QByteArray();
  }

  virtual void nextStep(){};

  virtual QVector3D* getPosition() { return position; }
  virtual int getType() { return type; }
  virtual InfinityDouble* getHelth() { return helth; }
  virtual InfinityDouble* getWeight() { return weight; }
  virtual InfinityDouble* getMaxTransitWeight() { return transitWeight; }
  virtual QString* getName() { return &name; }
  virtual QByteArray* getAdditionalData() { return additionalData; }

  friend QDataStream& operator<<(QDataStream& stream,
                                 const IBaseGameElement& myclass) {
    return stream << (*myclass.position) << (*myclass.helth)
                  << (*myclass.weight) << (*myclass.transitWeight)
                  << (*myclass.additionalData) << myclass.type << myclass.name
                  << myclass.rVision;
  }
  friend QDataStream& operator>>(QDataStream& stream,
                                 IBaseGameElement& myclass) {
    return stream >> (*myclass.position) >> (*myclass.helth) >>
           (*myclass.weight) >> (*myclass.transitWeight) >>
           (*myclass.additionalData) >> myclass.type >> myclass.name >>
           myclass.rVision;
    ;
  }

  virtual ~IBaseGameElement() {
    delete helth;
    delete weight;
    delete transitWeight;
    delete position;
  }

  virtual void setPosition(QVector3D* value) { this->position = value; }

  virtual void setHelth(InfinityDouble* value) { this->helth = value; }

  virtual void setWeight(InfinityDouble* value) { this->weight = value; }

  virtual void setTransitWeight(InfinityDouble* value) {
    this->transitWeight = value;
  }

  virtual void setType(int value) { this->type = value; }

  virtual void setName(QString name) { this->name = name; }

  virtual void setAdditionakData(QByteArray* data) {
    this->additionalData = data;
  }

  virtual void setRVision(int _rVison) { rVision = _rVison; }

  virtual int getRVision() { return rVision; }

 signals:

 public slots:

 protected:
  QVector3D* position = nullptr;
  InfinityDouble* helth = nullptr;
  InfinityDouble* weight = nullptr;
  InfinityDouble* transitWeight = nullptr;
  QByteArray* additionalData = nullptr;
  int rVision = 1;

  int type = -1;
  QString name;
};

#endif  // IBASEGAMEELEMENT_H
