#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H

#include <QObject>
#include <QTcpSocket>
class FtpCommand : public QObject
{
    Q_OBJECT
public:
    explicit FtpCommand(QObject *parent = 0);

    void start(QTcpSocket *socket);

signals:
    void reply(const QString &details);

protected:
    virtual void startImplementation() = 0;
    QTcpSocket* socket;
    bool started;
};

#endif // FTPCOMMAND_H
