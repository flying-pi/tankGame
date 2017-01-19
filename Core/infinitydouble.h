#ifndef WEIGHT_H
#define WEIGHT_H

#include <QDataStream>

class InfinityDouble : public QObject {
  Q_OBJECT

  friend QDataStream& operator<<(QDataStream& stream,
                                 const InfinityDouble& myclass) {
    return stream << myclass.isInfinity << myclass.w;
  }

  friend QDataStream& operator>>(QDataStream& stream, InfinityDouble& myclass) {
    return stream >> myclass.isInfinity >> myclass.w;
  }

 private:
  InfinityDouble();
  double w;
  bool isInfinity = false;

 public:
  static InfinityDouble* FromValue(double w);
  static InfinityDouble* InfinityValue();
};

#endif  // WEIGHT_H
