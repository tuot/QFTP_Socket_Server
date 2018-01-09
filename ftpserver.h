#ifndef FTPSERVER_H
#define FTPSERVER_H

#include <QObject>
#include <QTcpServer>
class FtpServer : public QObject
{
    Q_OBJECT
public:
    explicit FtpServer(QObject *parent,const QMap<QString,QString> &mapServerSetting,
                       const QMap<QString,bool> &mapFileLimit);



signals:
    void AddIpListSig(const QString IpAddress);

public slots:

private slots:
    void StartNewControlConnection();

private:
    QMap<QString,QString> mapServerSetting;
    QMap<QString,bool> mapFileLimit;

    QTcpServer *server;

    QSet<QString> encounteredIps;
};

#endif // FTPSERVER_H
