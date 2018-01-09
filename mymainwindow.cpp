#include "mymainwindow.h"
#include "ui_mymainwindow.h"

#include <QHostInfo>
#include <QFileDialog>
#include <QMessageBox>

static MyMainWindow *deBug = 0;

void myMessageOutput(QtMsgType /*type*/, const QMessageLogContext &/*context*/, const QString &msg)
{
    deBug->AppendDebugText(msg);
}

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
   ui->setupUi(this);
    deBug = this;

   this->setMaximumHeight(400);
   this->setMinimumHeight(400);
   this->setMaximumWidth(600);
   this->setMinimumWidth(600);

   this->GetLocalIP();
   ui->pushButtonStartServer->setEnabled(true);
   ui->pushButtonStopServer->setEnabled(false);
   server = 0;

   qInstallMessageHandler(myMessageOutput);

   ui->textEdit->setContextMenuPolicy(Qt::NoContextMenu);
}





MyMainWindow::~MyMainWindow()
{
    qInstallMessageHandler(0);
    delete ui;
}

QString MyMainWindow::GetLocalIP()
{
    QString localHostName = QHostInfo::localHostName();

    qDebug() <<"localHostName:"<<localHostName;
    int i=0;
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            qDebug() <<"IPV4 Address: "<< address.toString();
            ui->comboBoxIPAddress->insertItem(i++,address.toString());
        }
    }
    return 0;
}

void MyMainWindow::AddIpListSlot(QString IpAddress)
{
    if(ipList.contains(IpAddress))
    {
        return;
    }
    ipList.append(IpAddress);
    ui->listWidgetIPAddress->addItem(IpAddress);
}

void MyMainWindow::on_pushButtonStartServer_clicked()
{
    this->StartServer();
}

void MyMainWindow::StartServer()
{
    QString iUser=ui->lineEditUser->text();
    QString iPassword=ui->lineEditPassword->text();
    QString iPort=ui->lineEditPort->text();
    QString iRootPath=ui->lineEditRootPath->text();

    QString patternUser("^[a-z0-9_-]{3,16}$");
    QRegExp rxUser(patternUser);

    QString patternPassword("^[a-z0-9_-]{2,18}$");
    QRegExp rxPassword(patternPassword);




    if(!ui->checkBoxAllowAnyOneLogin->isChecked())
    {
        if(!rxUser.exactMatch(iUser))
        {
            QMessageBox::information(this,tr("错误"),tr("用户名输入错误！"),QMessageBox::Ok);
            return;
        }
        else if(!rxPassword.exactMatch(iPassword))
        {
            QMessageBox::information(this,tr("错误"),tr("密码输入错误！"),QMessageBox::Ok);
            return;
        }
    }

    if(iPort.isEmpty())
    {
        QMessageBox::information(this,tr("错误"),tr("端口输入错误！"),QMessageBox::Ok);
        return;
    }
    if(iRootPath.isEmpty()||iRootPath[0]==' ')
    {
        QMessageBox::information(this,tr("错误"),tr("文件路径不能为空！"),QMessageBox::Ok);
        return;
    }
    this->LoadSettings();

    if(server!=NULL)
    {
        delete server;
    }
    server = new FtpServer(this,mapServerSetting,mapFileLimit);
    qDebug()<<"服务启动成功!";
    connect(server,&FtpServer::AddIpListSig,this,&MyMainWindow::AddIpListSlot);

    ui->pushButtonStopServer->setEnabled(true);
    ui->pushButtonStartServer->setText(tr("重启服务"));
}

void MyMainWindow::on_toolButtonRootPath_clicked()
{
    QString rootPath;
    rootPath = QFileDialog::getExistingDirectory(this, QString(), ui->lineEditRootPath->text());

    if (rootPath.isEmpty()) {
        return;
    }
    ui->lineEditRootPath->setText(rootPath);
}

void MyMainWindow::on_pushButtonStopServer_clicked()
{
    this->StopServer();
}

void MyMainWindow::on_pushButtonDeleteIP_clicked()
{
    if(ui->listWidgetIPAddress->currentItem()!=Q_NULLPTR)
    {
        QListWidgetItem *item = ui->listWidgetIPAddress->takeItem(ui->listWidgetIPAddress->currentRow());
        delete item;
    }
    ui->textEdit->clear();
}

void MyMainWindow::LoadSettings()
{
//    mapServerSetting = new QMap<QString,QString>;
//    mapFileLimit = new QMap<QString,bool>;
    mapServerSetting.clear();
    mapFileLimit.clear();

    mapServerSetting.insert(QString("IPAddress"),ui->comboBoxIPAddress->currentText());
    mapServerSetting.insert(QString("IPPort"),ui->lineEditPort->text());

    mapServerSetting.insert(QString("RootPath"),ui->lineEditRootPath->text());

    mapFileLimit.insert(QString("OnlyWrite"),ui->checkBoxOnlyWrite->isChecked());
    mapFileLimit.insert(QString("OnlyRead"),ui->checkBoxOnlyRead->isChecked());
    mapFileLimit.insert(QString("AllowAnyOneLogin"),ui->checkBoxAllowAnyOneLogin->isChecked());
    if(ui->checkBoxAllowAnyOneLogin->isChecked()==true)
    {
        mapServerSetting.insert(QString("UserName"),QString(""));
        mapServerSetting.insert(QString("UserPassword"),QString(""));
    }
    else
    {
        mapServerSetting.insert(QString("UserName"),ui->lineEditUser->text());
        mapServerSetting.insert(QString("UserPassword"),ui->lineEditPassword->text());
    }
    mapFileLimit.insert(QString("AllowOneIP"),ui->checkBoxAllowOneIP->isChecked());


}

void MyMainWindow::StopServer()
{
    ui->pushButtonStopServer->setEnabled(false);
    ui->pushButtonStartServer->setText(tr("开启服务"));
    delete server;
    server = NULL;
    ipList.clear();
    int counter =ui->listWidgetIPAddress->count();
   for(int index=0;index<counter;index++)
   {
       QListWidgetItem *item = ui->listWidgetIPAddress->takeItem(0);
           delete item;
   }
    qDebug()<<"服务停止成功!";
}

void MyMainWindow::AppendDebugText(const QString &text)
{
    if(text==("show keyboard \n") || text==("hide keyboard \n") )
    {
        return;
    }
    ui->textEdit->append(text);
}
