#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection/simpleconnection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

 protected:
  void connectToServer();
  SimpleConnection connection;

 private slots:
  void on_testbtn_clicked();

 private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
