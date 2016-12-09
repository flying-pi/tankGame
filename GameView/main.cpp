#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  qSetMessagePattern("%{time boot} :: %{message}");
  MainWindow w;
  w.show();

  return a.exec();
}
