#include "field.h"
#include <QDebug>

Field::Field(QWidget* parent) : QGLWidget(parent) {}

Field::~Field() {}

void Field::onDiffReceive(QList<DiffElement*>* diff) {
  for (int i = 0; i < diff->length(); i++) {
    qInfo() << diff->at(i)->data->getPosition();
  }
}
void Field::initializeGL() {}

void Field::resizeGL(int w, int h) {}

void Field::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
