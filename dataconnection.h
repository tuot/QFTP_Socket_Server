#ifndef DATACONNECTION_H
#define DATACONNECTION_H
#include "ftpcommand.h"
#include <QTcpServer>
#include <QTcpSocket>

#include <QObject>
#include <QPointer>
class FtpCommand;

class DataConnection : public QObject
{
    Q_OBJECT
public:
    explicit DataConnection(QObject *parent = 0);

    void scheduleConnectToHost(const QString &hostName, int port, bool encrypt);

    int listen(bool encrypt);

    bool setFtpCommand(FtpCommand *command);

    FtpCommand *ftpCommand();
signals:

private slots:
    void newConnection();
    void encrypted();
    void connected();


private:
    void startFtpCommand();
    QTcpServer *server;
    QTcpSocket *socket;
    QPointer<FtpCommand> command;
    bool isSocketReady;
    bool isWaitingForFtpCommand;
    bool encrypt;

    // Used for the active data connection (PORT command).
    bool isActiveConnection;
    QString hostName;
    int port;
};

#endif // DATACONNECTION_H
