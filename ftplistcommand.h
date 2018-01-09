#ifndef FTPLISTCOMMAND_H
#define FTPLISTCOMMAND_H

#include "ftpcommand.h"

#include<QTimer>
#include<QFileInfo>


typedef QList<QFileInfo> QFileInfoList;

class FtpListCommand : public FtpCommand
{
public:
    explicit FtpListCommand(QObject *parent, const QString &listDirectory,
                            bool nameListOnly = false);
    ~FtpListCommand();
private:
    void startImplementation();
    QString fileListingString(const QFileInfo &fi);
private slots:
    void listNextBatch();

private:
    QString listDirectory;
    bool nameListOnly;
    QTimer *timer;
    QFileInfoList *list;
    int index;
};

#endif // FTPLISTCOMMAND_H
