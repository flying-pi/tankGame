#ifndef FIELD_H
#define FIELD_H
#include <QGLWidget>
#include <ibasegameelement.h>

#include <diffs/diffelement.h>
#include <diffs/diffcard.h>
#include "imap.h"

class Field : public QGLWidget {
  Q_OBJECT
 public:
  Field(QWidget* parent = 0);
  ~Field();

 public slots:
  void onDiffReceive(QList<DiffElement*>* diff);
  // QGLWidget interface
 protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int w, int h) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  void initRes();

  void drawGrass(float x, float y);

  GLuint grass;

  float scaleK = 0.005;

  DiffCard* diff;
  IMap* map;
};

#endif  // FIELD_H
