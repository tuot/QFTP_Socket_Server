#include "ftpcommand.h"

FtpCommand::FtpCommand(QObject *parent) : QObject(parent)
{
    started = false;
}

void FtpCommand::start(QTcpSocket *socket)
{
    started = true;
    this->socket = socket;
    socket->setParent(this);
    connect(socket, &QTcpSocket::disconnected, this, &FtpCommand::deleteLater);
    startImplementation();
}
