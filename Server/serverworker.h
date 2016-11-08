#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QTcpSocket>
#include <QThread>

class ServerWorker : public QThread
{
public:
    ServerWorker(QTcpSocket *socket);

    // QThread interface
protected:
    void run();

private:
    QTcpSocket *socket;
};

#endif // SERVERWORKER_H
