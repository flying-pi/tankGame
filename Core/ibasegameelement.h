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

enum eDiffType { eNew, eChange, eDeleted };
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
                  << (*myclass.weight) << (*myclass.transitWeight);
  }
  friend QDataStream& operator>>(QDataStream& stream,
                                 IBaseGameElement& myclass) {
    return stream >> (*myclass.position) >> (*myclass.helth) >>
           (*myclass.weight) >> (*myclass.transitWeight);
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

 signals:

 public slots:

 protected:
  QVector3D* position = nullptr;
  InfinityDouble* helth = nullptr;
  InfinityDouble* weight = nullptr;
  InfinityDouble* transitWeight = nullptr;
  QByteArray* additionalData = nullptr;

  int type = -1;
  QString name;
};

class DiffElement {
 public:
  DiffElement() { data = new IBaseGameElement(); }
  DiffElement(eDiffType type, IBaseGameElement* data) {
    this->type = type;
    this->data = data;
  }

  friend QDataStream& operator<<(QDataStream& stream,
                                 const DiffElement& myclass) {
    stream << ((int)myclass.type);
    IBaseGameElement& gameElement = (*myclass.data);
    return stream << gameElement;
  }
  friend QDataStream& operator>>(QDataStream& stream, DiffElement& myclass) {
    int type;
    QDataStream& result = stream >> type >> (*myclass.data);
    myclass.type = (eDiffType)type;
    return result;
  }

  eDiffType type;
  IBaseGameElement* data;
};

#endif  // IBASEGAMEELEMENT_H
