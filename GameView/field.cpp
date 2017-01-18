#include "field.h"
#include <QDebug>
#include "diffs/simplediffcard.h"
#include "maps/listbsemap.h"
#include <qtconcurrentrun.h>

Field::Field(QWidget* parent)
    : QGLWidget(parent), connection(QHostAddress::LocalHost, this) {
  diff = new SimpleDiffCard();
  map = new ListBseMap();
  initRes();
}

Field::~Field() {
  delete diff;
  delete map;
}

void Field::onDiffReceive(QList<DiffElement*>* diff) {
  this->diff->clear();
  this->diff->loadFromList(diff);
  map->updateFromDiff(this->diff);
  this->diff->clear();
  for (int i = 0; i < diff->size(); i++)
    delete diff->at(i);
  delete diff;
  update();
  QtConcurrent::run(QThreadPool::globalInstance(), [=] {
    QThread::msleep(100);
    this->connection.getBulder()->updateWatcher()->build();
  });
}
void Field::initializeGL() {}

void Field::resizeGL(int w, int h) {}

void Field::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  glTranslatef(-1, -1, 0);
  for (int i = 0; i < map->getCount(); i++) {
    auto currentElement = map->getElementAtPosition(i);
    if (currentElement->getType() == (int)eBaseGameElementType::eGrass) {
      drawGrass(currentElement->getPosition()->x(),
                currentElement->getPosition()->y());
    }
    if (currentElement->getType() == (int)eBaseGameElementType::eSimpleTank) {
      drawTank(currentElement->getPosition()->x(),
               currentElement->getPosition()->y());
    }
  }
  //  glTranslatef(1, 1, 0);
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
  loadTexture2((char*)":/res/grass.png", grass);
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

void Field::drawTank(float x, float y) {
  float size = scaleK;
  glColor3f(0.6862745098, 0.1215686275, 0.4156862745);
  glBegin(GL_QUADS);
  glVertex2f(x * this->scaleK, y * scaleK);
  glVertex2f(x * this->scaleK, y * scaleK + size * 2);
  glVertex2f(x * this->scaleK + size * 2, y * scaleK + size * 2);
  glVertex2f(x * this->scaleK + size * 2, y * scaleK);
  glEnd();
}
void Field::connectToServer() {
  if (isConnected)
    return;
  connection.openConnection();
  connect(&connection, SIGNAL(onDiffReceive(QList<DiffElement*>*)), this,
          SLOT(onDiffReceive(QList<DiffElement*>*)));
  connection.getBulder()->asFirstMessage(eConnectionType::eWatcher)->build();
  isConnected = true;
}
