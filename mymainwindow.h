#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "ftpserver.h"


namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();

    void AppendDebugText(const QString &text);
    friend void myMessageOutput(QtMsgType /*type*/, const QMessageLogContext &/*context*/, const QString &msg);

signals:
    void sendMsg(const QString &text);
private slots:

    void on_pushButtonStartServer_clicked();

    void on_toolButtonRootPath_clicked();

    void on_pushButtonStopServer_clicked();

    void on_pushButtonDeleteIP_clicked();

    void AddIpListSlot(QString IpAddress);

private:
    Ui::MyMainWindow *ui;

    FtpServer *server;

    QString GetLocalIP();

    void StartServer();

    void StopServer();

    void LoadSettings();

    QMap<QString,QString> mapServerSetting;
    QMap<QString,bool> mapFileLimit;

    QVector<QString> ipList;

};

#endif // MYMAINWINDOW_H
