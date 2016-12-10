#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  qSetMessagePattern(
      "%{time boot} :: [%{type}::%{appname} in %{file}:%{line} th:%{threadid}] "
      "message:: "
      "%{message} "
      "%{backtrace [separator=\"\n\t\"]}");
  //  qSetMessagePattern("%{time boot} :: %{message}");
  MainWindow w;
  w.show();

  return a.exec();
}
