#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      connection(QHostAddress::LocalHost, this) {
  ui->setupUi(this);
  connectToServer();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::connectToServer() {
  connection.openConnection();
  connection.getBulder()->asFirstMessage(eConnectionType::eWatcher)->build();
}

void MainWindow::on_testbtn_clicked() {
  connection.getBulder()->asFirstMessage(eConnectionType::eWatcher)->build();
}
