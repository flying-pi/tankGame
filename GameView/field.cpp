#include "field.h"
#include <QDebug>

Field::Field(QWidget* parent) : QGLWidget(parent) {
  fieldState = new QList<IBaseGameElement*>();
  initRes();
}

Field::~Field() {
  delete fieldState;
}

void Field::onDiffReceive(QList<DiffElement*>* diff) {
  for (int i = 0; i < diff->length(); i++) {
    if (diff->at(i)->type == eDiffType::eNew) {
      this->fieldState->append(diff->at(i)->data);
    }
  }
  update();
}
void Field::initializeGL() {}

void Field::resizeGL(int w, int h) {}

void Field::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef(-1, -1, 0);
  for (int i = 0; i < fieldState->length(); i++) {
    auto currentElement = fieldState->at(i);
    if (currentElement->getType() == (int)eBaseGameElementType::eGrass) {
      drawGrass(currentElement->getPosition()->x(),
                currentElement->getPosition()->y());
    }
  }
  glTranslatef(1, 1, 0);
  //  glEnd();

  //  glDisable(GL_TEXTURE_2D);
}

QImage loadTexture2(char* filename, GLuint& textureID) {
  glEnable(GL_TEXTURE_2D);  // Enable texturing

  glGenTextures(1, &textureID);             // Obtain an id for the texture
  glBindTexture(GL_TEXTURE_2D, textureID);  // Set as the current texture

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  QImage im(filename);
  QImage tex = QGLWidget::convertToGLFormat(im);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA,
               GL_UNSIGNED_BYTE, tex.bits());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glDisable(GL_TEXTURE_2D);

  return tex;
}

void Field::initRes() {
  loadTexture2(":/res/grass.png", grass);
}

void Field::drawGrass(float x, float y) {
  //  glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D, grass);

  //  glBegin(GL_QUADS);
  //  glTexCoord2f(0, 0);
  //  glVertex3f(-1, -1, -1);
  //  glTexCoord2f(1, 0);
  //  glVertex3f(1, -1, -1);
  //  glTexCoord2f(1, 1);
  //  glVertex3f(1, 1, -1);
  //  glTexCoord2f(0, 1);
  //  glVertex3f(-1, 1, -1);
  // .....
  //  glDisable(GL_TEXTURE_2D);
  float size = scaleK;
  glColor3f(0.560, 0.956, 0.258);
  glBegin(GL_QUADS);
  glVertex2f(x * this->scaleK, y * scaleK);
  glVertex2f(x * this->scaleK, y * scaleK + size);
  glVertex2f(x * this->scaleK + size, y * scaleK + size);
  glVertex2f(x * this->scaleK + size, y * scaleK);
  glEnd();
}
