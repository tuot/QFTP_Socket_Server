#include "ftpserver.h"
#include "ftpcontrolconnection.h"
#include <QTcpSocket>

FtpServer::FtpServer(QObject *parent, const QMap<QString, QString> &mapServerSetting,
                     const QMap<QString, bool> &mapFileLimit) : QObject(parent)
{
    this->mapFileLimit = mapFileLimit;
    this->mapServerSetting = mapServerSetting;

    int port=21;
    if(this->mapServerSetting.contains("IPPort"))
    {
        QMap<QString,QString>::iterator it = this->mapServerSetting.find("IPPort");
        bool ok;
         port = QString(it.value()).toInt(&ok,10);
        //qDebug()<<ok<<port;
    }

    server = new QTcpServer(this);
    server->listen(QHostAddress::AnyIPv4,port);
    connect(server,&QTcpServer::newConnection,this,&FtpServer::StartNewControlConnection);


}



void FtpServer::StartNewControlConnection()
{
    QTcpSocket *socket = (QTcpSocket *)server->nextPendingConnection();

    QString peerIp = socket->peerAddress().toString();
    qDebug() << "connection from" << peerIp;

    if (!encounteredIps.contains(peerIp))
    {
        // If we don't allow more than one IP for the client, we close
        // that connection.

        if(this->mapFileLimit.contains("AllowOneIP"))
        {

            QMap<QString,bool>::iterator it = this->mapFileLimit.find("AllowOneIP");
            if(it.value() && !encounteredIps.isEmpty())
            {
                delete socket;
                return;
            }
        }

        emit AddIpListSig(peerIp);
        encounteredIps.insert(peerIp);

    }

    new FtpControlConnection(this,socket,this->mapServerSetting,this->mapFileLimit);
}
