#include <QCoreApplication>
#include "gamer.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  Gamer gamer;
  gamer.startGamer();
  return a.exec();
}
