#include "mymainwindow.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/appicon"));

    QTranslator translator;
    translator.load(QString(":/trans/appstrans"));
    a.installTranslator(&translator);

    MyMainWindow w;
    w.show();



    return a.exec();
}
