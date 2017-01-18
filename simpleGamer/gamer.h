#ifndef GAMER_H
#define GAMER_H

#include <QObject>

#include <connection/simpleconnection.h>

class Gamer : public QObject {
  Q_OBJECT
 public:
  explicit Gamer(QObject* parent = 0);
  void startGamer();

 signals:

 public slots:

 protected:
  SimpleConnection connection;
  int count = 0;

 protected slots:
  void onDiffReceive(QList<DiffElement*>*);
};

#endif  // GAMER_H
