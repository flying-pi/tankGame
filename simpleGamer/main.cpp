#include <QCoreApplication>
#include "gamer.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);
  qSetMessagePattern(
      "%{time boot} :: [%{type}::%{appname} in %{file}:%{line} th:%{threadid}] "
      "message:: "
      "%{message} "
      "%{backtrace [separator=\"\n\t\"]}");
  QTime midnight(0, 0, 0);
  qsrand(midnight.secsTo(QTime::currentTime()));
  Gamer* gamer = new Gamer(&a);
  gamer->startGamer();
  return a.exec();
}
