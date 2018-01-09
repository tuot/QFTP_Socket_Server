#ifndef FTPCONTROLCONNECTION_H
#define FTPCONTROLCONNECTION_H

#include <QPointer>
#include <QObject>
#include <QTcpSocket>

class FtpCommand;
class DataConnection;

class FtpControlConnection : public QObject
{
    Q_OBJECT
public:
    explicit FtpControlConnection(QObject *parent, QTcpSocket *socket, const QMap<QString, QString> &mapServerSetting,
                                const QMap<QString, bool> &mapFileLimit);
    ~FtpControlConnection();

signals:

public slots:
    void reply(const QString &replyCode);

private slots:
    void AcceptNewData();
    void disconnectFromHost();

private:
    QString stripFlagL(const QString &fileName);

    void parseCommand(const QString &entireCommand, QString *command, QString *commandParameters);

    QString toLocalPath(const QString &fileName) const;

    void processCommand(const QString &entireCommand);
    void startOrScheduleCommand(FtpCommand *ftpCommand);




    void port(const QString &addressAndPort);

    void pasv();

    void list(const QString &dir, bool nameListOnly);

    void retr(const QString &fileName);

    void stor(const QString &fileName, bool appendMode = false);

    void cwd(const QString &dir);

    void mkd(const QString &dir);

    void rmd(const QString &dir);

    void dele(const QString &fileName);

    void rnto(const QString &fileName);

    void quit();

    void size(const QString &fileName);

    void pass(const QString &password);

    void auth();

    void prot(const QString &protectionLevel);

    void cdup();

    void feat();

    qint64 seekTo();

    QTcpSocket *socket;

    QString currentDirectory;

    QString lastProcessedCommand;

    bool isLoggedIn;

    bool encryptDataConnection;
    DataConnection *dataConnection;

    QMap<QString,QString> mapServerSetting;
    QMap<QString,bool> mapFileLimit;

    QString userName;
    QString password;
    QString rootPath;
    bool readOnly;
    bool writeOnly;

};

#endif // FTPCONTROLCONNECTION_H
