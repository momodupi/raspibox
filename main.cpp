#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen splash(QPixmap(":/system/src/splash.png"));
    splash.setWindowFlags(Qt::FramelessWindowHint);
    splash.setWindowState(Qt::WindowFullScreen);
    splash.show();

    QElapsedTimer delaytime;
    delaytime.start();
    while (delaytime.elapsed() < 666)
    {
        QCoreApplication::processEvents();
    }

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
