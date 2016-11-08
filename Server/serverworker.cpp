#include "serverworker.h"

ServerWorker::ServerWorker(QTcpSocket *socket)
{
    this->socket = socket;
}

void ServerWorker::run()
{

}
