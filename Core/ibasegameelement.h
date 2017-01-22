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

enum eBaseGameElementType { eGrass, eSimpleTank, eBasis, eBullet };
class IBaseGameElement;

struct GameElementData {
  QVector3D* position = nullptr;
  InfinityDouble* helth = nullptr;
  InfinityDouble* weight = nullptr;
  InfinityDouble* transitWeight = nullptr;
  QByteArray* additionalData = nullptr;
  qint32 rVision = 1;
  qint32 type = -1;
  QString name = "";

  ~GameElementData() {
    delete position;
    delete helth;
    delete weight;
    delete transitWeight;
    delete additionalData;
  }

  void defaultInit() {
    position = new QVector3D(0, 0, 0);
    helth = InfinityDouble::FromValue(1);
    weight = InfinityDouble::FromValue(0);
    transitWeight = InfinityDouble::FromValue(0);
    additionalData = new QByteArray();
  }
};

extern QDataStream& operator>>(QDataStream& stream, GameElementData& myclass);
extern QDataStream& operator<<(QDataStream& stream, GameElementData& myclass);

class IBaseGameElement : public QObject {
  Q_OBJECT
 public:
  IBaseGameElement() {
    helth = InfinityDouble::FromValue(1);
    weight = InfinityDouble::FromValue(0);
    transitWeight = InfinityDouble::FromValue(0);
    position = new QVector3D(0, 0, 0);
    name = "";
    additionalData = new QByteArray();
  }

  IBaseGameElement(GameElementData& data) { init(data); }

  virtual void nextStep(){};

  virtual QVector3D* getPosition() const { return position; }
  virtual int getType() const { return type; }
  virtual InfinityDouble* getHelth() const { return helth; }
  virtual InfinityDouble* getWeight() const { return weight; }
  virtual InfinityDouble* getMaxTransitWeight() const { return transitWeight; }
  virtual QString getName() const { return name; }
  virtual QByteArray* getAdditionalData() const { return additionalData; }
  virtual int getRVision() const { return rVision; }

  friend QDataStream& operator<<(QDataStream& stream,
                                 const IBaseGameElement& myclass) {
    return stream << (*myclass.position) << (*myclass.helth)
                  << (*myclass.weight) << (*myclass.transitWeight)
                  << (*myclass.additionalData) << myclass.type << myclass.name
                  << myclass.rVision;
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

  void copyData(GameElementData& out);
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

  virtual void init(GameElementData& data);
};

#endif  // IBASEGAMEELEMENT_H
