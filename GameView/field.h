#ifndef FIELD_H
#define FIELD_H
#include <QGLWidget>
#include <ibasegameelement.h>

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
};

#endif  // FIELD_H
