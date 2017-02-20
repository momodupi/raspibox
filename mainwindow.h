#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QTime>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QDir>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QProcess>
#include <QPicture>
#include <QTextCodec>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QVariant>
#include <QScrollBar>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QFile>



namespace Ui {
class MainWindow;
}

//weather struct


typedef struct
{
    QString date;
    QString tempmax;
    QString tempmin;
    QString type;
    QString winddir;
    QString windpow;
    QString reserve;
}weatherforecast_def;

typedef struct
{
    QString city;
    QString updatetime;
    QString temperature;
    QString winddir;
    QString humidity;
    QString windpow;
    QString sunrise;
    QString sunset;
    //environment
    QString AQI;
    QString PM25;
    QString airquality;
    QString o3;
    QString co;
    QString pm10;
    QString so2;
    QString no2;
    //alarm
    QString alarmtype;
    QString alarmdegree;
    QString alarmtext;
    QString alarmdetails;
    QString alarmstandard;
    QString alarmsuggest;
    QString alarmimgurl;
    //forecast
    weatherforecast_def weatherforecast[5];
} weathernow_def;

typedef union
{
    struct
    {
        int user;
        int nice;
        int system;
        int idle;
        int iowait;
        int irq;
        int softirq;
        int stealstolen;
        int guest;
    }members;

    int frame[9];

}cpuinfo_def;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_sidebarlistWidget_clicked(const QModelIndex &index);

    void qtimer_timeout_Slot(void);

    void qtimer_textscrolling_Slot(void);

    void on_videolistWidget_clicked(const QModelIndex &index);

    void on_videoplayButton_clicked();

    void on_videodeleteButton_clicked();


    void on_videorefreshButton_clicked();

    void on_piclistWidget_clicked(const QModelIndex &index);

    void on_picdirlistWidget_clicked(const QModelIndex &index);

    void on_poweroffButton_clicked();

    void on_rebootButton_clicked();

    void on_settingsaveButton_clicked();

    void on_settingredoButton_clicked();

    void on_nettableWidget_doubleClicked(const QModelIndex &index);

protected slots:
    void replayFinished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    QDir videodir;
    QFileInfo videoinfo;

    QString videoprgm;
    QString videopath;
    QString videodirpath;
    QFileInfoList videinfolist;
    QString videofrmsdirpath;
    QString videofrmspath;
    QFileInfo videosnpImgFileInfo;

    QString videofileName;
    QImage videosnpImg;

    //weather relavent
    //weatherforecast_def weatherforecast[5];
    weathernow_def weathernow;
    QNetworkAccessManager *manager;    
    QString city, weatherURL;
    void parseXml(QString Xml);

    QDir picturefthdir;
    QDir picturedir;
    QFileInfo picturedirinfo;
    QFileInfo pictureinfo;
    QString picturedirpath;
    QString picturechddirpath;
    QString picturepath;
    QFileInfoList picturedirinfolist;
    QFileInfoList pictureinfolist;

    QString picturefileName;
    QImage pictureImg;

    QSize resizepicture(QSize picturesize, QSize labelsize);

    int calculateCPUusage(void);
    int calculatememusage(void);
    int calculatedisksage(void);

};

#endif // MAINWINDOW_H
