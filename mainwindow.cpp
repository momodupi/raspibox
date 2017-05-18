#include "mainwindow.h"
#include "ui_mainwindow.h"

#define RASPBERRY


#define DEFAULTCITY             "沈阳"

#ifdef RASPBERRY

#define VIDEODIR_PATH           "/mnt/disk/Videos"
#define VIDEOSNAPDIR_PATH       "/mnt/disk/Videos/snap"
#define PICTUREDIR_PATH         "/mnt/disk/Pictures"

#else

#define VIDEODIR_PATH           "/mnt/hgfs/HomeGroup"
#define VIDEOSNAPDIR_PATH       "/home/momodupi/Pictures/snap"
#define PICTUREDIR_PATH         "/home/momodupi/Pictures"

#endif

enum emainstackwidegt
{
    MAINSW_STARTPAGE = 0,
    MAINSW_VIDEOPAGE,
    MAINSW_PICTUREPAGE,
    MAINSW_NETPAGE,
    MAINSW_SETTINGPAGE

};

/*
enum eweathertype
{
    WTHRTYPE_IPLOCATING = 0,
    WTHRTYPE_WEATHERNOW,
    WTHRTYPE_FORECAST
};*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:#263238");

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowFullScreen);

    setMouseTracking(true);

/**/
    ui->sidebarlistWidget->addItem(new QListWidgetItem(tr("开始")));
    ui->sidebarlistWidget->addItem(new QListWidgetItem(tr("视频")));
    ui->sidebarlistWidget->addItem(new QListWidgetItem(tr("图片")));
    ui->sidebarlistWidget->addItem(new QListWidgetItem(tr("网络")));
    ui->sidebarlistWidget->addItem(new QListWidgetItem(tr("设置")));

    ui->sidebarlistWidget->setFrameShape(QListWidget::NoFrame);
    ui->sidebarlistWidget->setStyleSheet("color:#d4d4d4; background-color:#2c3e5c");
    ui->sidebarlistWidget->setFont(QFont("San Serif", 20));

    for (int cnt = 0; cnt < ui->sidebarlistWidget->count(); cnt++)
    {
        QListWidgetItem *item = ui->sidebarlistWidget->item(cnt);
        item->setSizeHint(QSize(item->sizeHint().width(), 80));
        item->setTextAlignment(Qt::AlignCenter);
    }
    ui->sidebarlistWidget->setCurrentItem(ui->sidebarlistWidget->item(0));
    ui->sidebarlistWidget->setCurrentRow(0);

    QGraphicsDropShadowEffect *sidebarlistWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    sidebarlistWidget_shadoweffect->setOffset(0, 0);
    sidebarlistWidget_shadoweffect->setColor("#000000");
    sidebarlistWidget_shadoweffect->setBlurRadius(30);
    ui->sidebarlistWidget->setGraphicsEffect(sidebarlistWidget_shadoweffect);

    ui->mainstackedWidget->setCurrentIndex(MAINSW_STARTPAGE);

    //start page
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(qtimer_timeout_Slot()));
    timer->start(1000);

    ui->weatherbglabel->setStyleSheet("background-color:#424242");
    ui->weatherbglabel->setText("");
    QGraphicsDropShadowEffect *weatherbglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    weatherbglabel_shadoweffect->setOffset(0, 0);
    weatherbglabel_shadoweffect->setColor("#000000");
    weatherbglabel_shadoweffect->setBlurRadius(30);
    ui->weatherbglabel->setGraphicsEffect(weatherbglabel_shadoweffect);

    ui->citylabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->citylabel->setFont(QFont("San Serif", 32));
    ui->citylabel->setText("");
    ui->tempnowlabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->tempnowlabel->setFont(QFont("San Serif", 72));
    ui->tempnowlabel->setText("");
    ui->weatherlabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->weatherlabel->setFont(QFont("San Serif", 24));
    ui->weatherlabel->setText("");
    ui->AQIlabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->AQIlabel->setFont(QFont("San Serif", 16));
    ui->AQIlabel->setText("");
    ui->weatherinfolabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->weatherinfolabel->setFont(QFont("San Serif", 16));
    ui->weatherinfolabel->setText("");
    ui->weatherpiclabel->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->weatherpiclabel->setFont(QFont("San Serif", 32));
    ui->weatherpiclabel->setText("");

    ui->weathertableWidget->verticalHeader()->setVisible(false);
    ui->weathertableWidget->horizontalHeader()->setVisible(false);
    ui->weathertableWidget->setFrameShape(QFrame::NoFrame);
    ui->weathertableWidget->setShowGrid(false);
    ui->weathertableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->weathertableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->weathertableWidget->setColumnWidth(0, 120);
    ui->weathertableWidget->setColumnWidth(1, 100);
    ui->weathertableWidget->setColumnWidth(2, 130);
    ui->weathertableWidget->setRowHeight(0, 100);
    ui->weathertableWidget->setRowHeight(1, 100);
    ui->weathertableWidget->setRowHeight(2, 100);
    ui->weathertableWidget->setRowHeight(3, 100);
    ui->weathertableWidget->setStyleSheet("color:#d4d4d4; background-color:#757575;");
    ui->weathertableWidget->setFont(QFont("San Serif", 16));
    QGraphicsDropShadowEffect *weathertableWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    weathertableWidget_shadoweffect->setOffset(0, 0);
    weathertableWidget_shadoweffect->setColor("#000000");
    weathertableWidget_shadoweffect->setBlurRadius(30);
    ui->weathertableWidget->setGraphicsEffect(weathertableWidget_shadoweffect);

    ui->weathernoselectlabel->setText("");
    ui->weathernoselectlabel->setStyleSheet("background:transparent");

    ui->clockbglabel->setStyleSheet("background-color:#01579b");
    ui->clockbglabel->setText("");
    QGraphicsDropShadowEffect *clockbglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    clockbglabel_shadoweffect->setOffset(0, 0);
    clockbglabel_shadoweffect->setColor("#000000");
    clockbglabel_shadoweffect->setBlurRadius(30);
    ui->clockbglabel->setGraphicsEffect(clockbglabel_shadoweffect);

    //QString hourminute = time.toString("hh : mm");
    //QString second = time.toString("ss");
    manager = new QNetworkAccessManager(this);
    //weather API
    //weatherURL_1 = "http://wthrcdn.etouch.cn/weather_mini?city=";
    //weatherURL = "http://wthrcdn.etouch.cn/WeatherApi?city=";
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
    //locating based on IP address
    //weathertype = 0;
    //manager->get(QNetworkRequest(QUrl("http://int.dpool.sina.com.cn/iplookup/iplookup.php")));
    city = DEFAULTCITY;
    //QString url = weatherURL + city;
    QString url = "http://wthrcdn.etouch.cn/WeatherApi?citykey=101070101";
    manager->get(QNetworkRequest(QUrl(url)));

    QDateTime time = QDateTime::currentDateTime();
    QString datemonth = time.toString("M");
    QString dateday = time.toString("d");
    QString weekday = time.toString("ddd");
    ui->datebglabel->setStyleSheet("background-color:#0288d1");
    ui->datebglabel->setText("");
    QGraphicsDropShadowEffect *datebglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    datebglabel_shadoweffect->setOffset(0, 0);
    datebglabel_shadoweffect->setColor("#000000");
    datebglabel_shadoweffect->setBlurRadius(30);
    ui->datebglabel->setGraphicsEffect(datebglabel_shadoweffect);

    ui->datelabel->setStyleSheet("color:#d4d4d4; background-color:#0288d1");
    ui->datelabel->setFont(QFont("San Serif", 32));
    ui->datelabel->setText(datemonth + "月\n" + dateday + "日\n" + weekday);

    //video page
/*
    QString mntprgm = "mount";
    QString mntuidgid = "uid=pi,gid=pi";
    QString mntsrcpath = MNTSOURCEDIR_PATH;
    QString mnttrgtpath = MNTTARGETDIR_PATH;
    QStringList mntargm;
    mntargm << "-o" << mntuidgid << mntsrcpath << mnttrgtpath;

    QProcess *mnt_prcs = new QProcess(this);
    mnt_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    mnt_prcs->setReadChannel(QProcess::StandardOutput);
    mnt_prcs->start(mntprgm, mntargm);
    mnt_prcs->waitForFinished();
    mnt_prcs->close();
*/
    videodirpath = VIDEODIR_PATH;
    videodir.setPath(videodirpath);
    //tdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    //videodir.setSorting(QDir::DirsFirst | QDir::Size | QDir::Reversed);
    videodir.setSorting(QDir::DirsFirst | QDir::Time);
    videodir.setFilter(QDir::Files);

    videinfolist = videodir.entryInfoList();

    for (int cnt = 0, rcnt = 0; cnt < videinfolist.size(); cnt++)
    {
        videoinfo = videinfolist.at(cnt);

        //output frameshot: ffmpeg -i /mnt/hgfs/HomeGroup/VID_20151231_214801.mp4 -y -f mjpeg -ss 3 -t 0.001 -s 320X240 ~/test.jpg
        videopath = videodirpath + "/" + videoinfo.fileName();
        videofrmsdirpath = VIDEOSNAPDIR_PATH;

        videosnpImgFileInfo.setFile(videofrmsdirpath, videoinfo.fileName());
        if (videosnpImgFileInfo.isFile() == false)
        {
            videofrmspath = videofrmsdirpath + "/" + videoinfo.fileName();
            videoprgm = "ffmpeg";
            int rcnt = qrand() % 1000;
            QString videofrmstime = QString::number(rcnt, 10);
            QString videostime = "0.001";
            QString videofrmstype = "mjpeg";
            QString videofrmssize = "450x300";
            QStringList videoargm;
            videoargm << "-i" << videopath << "-y" << "-f" << videofrmstype << "-ss" << videofrmstime << "-t" << videostime << "-s" << videofrmssize << videofrmspath;

            QProcess *ffmpeg_prcs = new QProcess(this);

            ffmpeg_prcs->setProcessChannelMode(QProcess::SeparateChannels);
            ffmpeg_prcs->setReadChannel(QProcess::StandardOutput);
            ffmpeg_prcs->start(videoprgm, videoargm);
            ffmpeg_prcs->waitForFinished();
            ffmpeg_prcs->close();
        }

        QString filesuffix;
        filesuffix = videoinfo.suffix();
        if ((filesuffix == "mkv")  ||
            (filesuffix == "avi")  ||
            (filesuffix == "mp4")  ||
            (filesuffix == "rmvb") ||
            (filesuffix == "rm")   ||
            (filesuffix == "flv"))
        {
            //ui->videolistWidget->addItem(new QListWidgetItem(QIcon(videofrmspath), videoinfo.fileName()));
            ui->videolistWidget->addItem(new QListWidgetItem(videoinfo.fileName()));

            //rcnt removes void lists
            QListWidgetItem *item = ui->videolistWidget->item(rcnt++);
            item->setSizeHint(QSize(item->sizeHint().width(), 36));
            item->setTextAlignment(Qt::AlignLeft);
            //item->setTextColor("#a2d0ea");
            //item->setFont(QFont("San Serif", 16));
        }
    }
    ui->videolistWidget->setCurrentRow(0);
    //ui->videolistWidget->setViewMode(QListView::IconMode);
    //ui->videolistWidget->setIconSize(QSize(320, 240));
    //ui->videolistWidget->setFrameShape(QListWidget::NoFrame);
    //ui->videolistWidget->setStyleSheet("border: 1px solid #4682B4;");
    ui->videolistWidget->setFrameShape(QListWidget::NoFrame);
    ui->videolistWidget->setStyleSheet("color:#d4d4d4; background-color:#01579b");
    ui->videolistWidget->setFont(QFont("San Serif", 16));
    ui->videolistWidget->setCurrentItem(ui->videolistWidget->item(0));

    ui->videolistWidget->verticalScrollBar()->setStyleSheet("color:#d4d4d4; background-color:#01579b");
    QGraphicsDropShadowEffect *videolistWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    videolistWidget_shadoweffect->setOffset(0, 0);
    videolistWidget_shadoweffect->setColor("#000000");
    videolistWidget_shadoweffect->setBlurRadius(30);
    ui->videolistWidget->setGraphicsEffect(videolistWidget_shadoweffect);

    QString fileName = ui->videolistWidget->currentItem()->text();
    QString videoinfotitle = "上次观看：";
    videoinfo.setFile(videodirpath, fileName);
    QDateTime lastreadtime = videoinfo.lastRead();
    ui->videoinfolabel->setText(videoinfotitle + lastreadtime.toString("yyyy/MM/dd hh:mm:ss"));
    ui->videoinfolabel->setAlignment(Qt::AlignCenter);
    ui->videoinfolabel->setFont(QFont("San Serif", 14));
    //ui->videoinfolabel->setStyleSheet("color:#c5cae9; background-color:#1a237e");
    ui->videoinfolabel->setStyleSheet("color:#d4d4d4; background-color:#424242");

    videofrmsdirpath = VIDEOSNAPDIR_PATH;
    QString filesuffix = videoinfo.suffix();
    if ((filesuffix == "mkv")  ||
        (filesuffix == "avi")  ||
        (filesuffix == "mp4")  ||
        (filesuffix == "flv"))
    {
        videofrmspath = videofrmsdirpath + "/" + videoinfo.fileName();
        videosnpImg.load(videofrmspath);
        ui->videosnaplabel->setPixmap(QPixmap::fromImage(videosnpImg));
        ui->videosnaplabel->setScaledContents(true);
        ui->videosnaplabel->resize(ui->videosnaplabel->width(), ui->videosnaplabel->height());
    }
    else  if ((filesuffix == "rm")     ||
                 (filesuffix == "rmvb"))
    {
        ui->videosnaplabel->setStyleSheet("color:#d4d4d4");
        ui->videosnaplabel->setFont(QFont("San Serif", 12));
        ui->videosnaplabel->setAlignment(Qt::AlignCenter);
        ui->videosnaplabel->setText("rm/rmvb格式会存在卡顿");
    }
    QGraphicsDropShadowEffect *videosnaplabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    videosnaplabel_shadoweffect->setOffset(0, 0);
    videosnaplabel_shadoweffect->setColor("#000000");
    videosnaplabel_shadoweffect->setBlurRadius(30);
    ui->videosnaplabel->setGraphicsEffect(videosnaplabel_shadoweffect);

    ui->videobglabel->setText("");
    ui->videobglabel->setStyleSheet("background-color:#424242");
    QGraphicsDropShadowEffect *videobglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    videobglabel_shadoweffect->setOffset(0, 0);
    videobglabel_shadoweffect->setColor("#000000");
    videobglabel_shadoweffect->setBlurRadius(30);
    ui->videobglabel->setGraphicsEffect(videobglabel_shadoweffect);

    ui->videonamelabel->setText(fileName);
    ui->videonamelabel->setStyleSheet("color:#d4d4d4; background-color:#0277bd");
    ui->videonamelabel->setFont(QFont("San Serif", 40));
    QGraphicsDropShadowEffect *videonamelabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    videonamelabel_shadoweffect->setOffset(0, 0);
    videonamelabel_shadoweffect->setColor("#000000");
    videonamelabel_shadoweffect->setBlurRadius(30);
    ui->videonamelabel->setGraphicsEffect(videonamelabel_shadoweffect);

    QTimer *scrollingtimer = new QTimer(this);
    connect(scrollingtimer, SIGNAL(timeout()), this, SLOT(qtimer_textscrolling_Slot()));
    scrollingtimer->start(400);

    ui->videoplayButton->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->videoplayButton->setText("");
    ui->videoplayButton->setIcon(QIcon(":/system/src/play.png"));
    QGraphicsDropShadowEffect *videoplayButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    videoplayButton_shadoweffect->setOffset(0, 0);
    videoplayButton_shadoweffect->setColor("#212121");
    videoplayButton_shadoweffect->setBlurRadius(20);
    ui->videoplayButton->setGraphicsEffect(videoplayButton_shadoweffect);

    ui->videodeleteButton->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->videodeleteButton->setText("");
    ui->videodeleteButton->setIcon(QIcon(":/system/src/delete.png"));
    ui->videodeleteButton->setFont(QFont("San Serif", 14));
    QGraphicsDropShadowEffect *videodeleteButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    videodeleteButton_shadoweffect->setOffset(0, 0);
    videodeleteButton_shadoweffect->setColor("#212121");
    videodeleteButton_shadoweffect->setBlurRadius(20);
    ui->videodeleteButton->setGraphicsEffect(videodeleteButton_shadoweffect);

    ui->videorefreshButton->setStyleSheet("color:#d4d4d4; background-color:#424242");
    ui->videorefreshButton->setText("");
    ui->videorefreshButton->setIcon(QIcon(":/system/src/refresh.png"));
    ui->videorefreshButton->setFont(QFont("San Serif", 14));
    QGraphicsDropShadowEffect *videorefreshButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    videorefreshButton_shadoweffect->setOffset(0, 0);
    videorefreshButton_shadoweffect->setColor("#212121");
    videorefreshButton_shadoweffect->setBlurRadius(20);
    ui->videorefreshButton->setGraphicsEffect(videodeleteButton_shadoweffect);

    //picture page
    ui->picdirlistWidget->setFrameShape(QFrame::NoFrame);
    ui->picdirlistWidget->setStyleSheet("color:#d4d4d4; background-color:#616161");
    ui->picdirlistWidget->setFlow(QListView::LeftToRight);
    ui->picdirlistWidget->setFont(QFont("San Serif", 14));
    QGraphicsDropShadowEffect *picdirtableWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    picdirtableWidget_shadoweffect->setOffset(0, 0);
    picdirtableWidget_shadoweffect->setColor("#000000");
    picdirtableWidget_shadoweffect->setBlurRadius(30);
    ui->picdirlistWidget->setGraphicsEffect(picdirtableWidget_shadoweffect);
    ui->picdirlistWidget->horizontalScrollBar()->setStyleSheet("color:#d4d4d4; background-color:#424242; ");

    picturedirpath = PICTUREDIR_PATH;
    picturefthdir.setPath(picturedirpath);
    //tdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    //videodir.setSorting(QDir::DirsFirst | QDir::Size | QDir::Reversed);
    picturefthdir.setSorting(QDir::Name | QDir::Time);
    picturefthdir.setFilter(QDir::Dirs);

    picturedirinfolist = picturefthdir.entryInfoList();
    for (int cnt = 0, ccnt = 0; cnt < picturedirinfolist.size(); cnt++)
    {
        picturedirinfo = picturedirinfolist.at(cnt);
        QString filesuffix;
        filesuffix = picturedirinfo.suffix();
        if ((filesuffix == "") && (picturedirinfo.fileName() != ".") && (picturedirinfo.fileName() != ".."))
        {
            ui->picdirlistWidget->addItem(new QListWidgetItem(picturedirinfo.fileName()));
            //rcnt removes void lists
            QListWidgetItem *item = ui->picdirlistWidget->item(ccnt++);
            item->setSizeHint(QSize(184, 20));
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->picdirlistWidget->setCurrentItem(ui->videolistWidget->item(0));
    ui->picdirlistWidget->setCurrentRow(0);

    ui->piclabel->setStyleSheet("background-color:#212121");
    ui->piclabel->setText("");

    ui->picbglabel->setStyleSheet("background-color:#212121");
    ui->picbglabel->setText("");
    QGraphicsDropShadowEffect *piclabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    piclabel_shadoweffect->setOffset(0, 0);
    piclabel_shadoweffect->setColor("#000000");
    piclabel_shadoweffect->setBlurRadius(30);
    ui->picbglabel->setGraphicsEffect(piclabel_shadoweffect);

    ui->piclistWidget->setFrameShape(QFrame::NoFrame);
    ui->piclistWidget->setStyleSheet("color:#d4d4d4; background-color:#424242; ");
    ui->piclistWidget->setFlow(QListView::LeftToRight);
    ui->piclistWidget->setViewMode(QListView::IconMode);
    ui->piclistWidget->setResizeMode(QListView::Adjust);
    ui->piclistWidget->verticalScrollBar()->setStyleSheet("color:#d4d4d4; background-color:#424242");
    QGraphicsDropShadowEffect *piclistWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    piclistWidget_shadoweffect->setOffset(0, 0);
    piclistWidget_shadoweffect->setColor("#000000");
    piclistWidget_shadoweffect->setBlurRadius(30);
    ui->piclistWidget->setGraphicsEffect(piclistWidget_shadoweffect);

    picturechddirpath = picturedirpath + "/" + ui->picdirlistWidget->currentItem()->text();
    picturedir.setPath(picturechddirpath);
    //tdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    //videodir.setSorting(QDir::DirsFirst | QDir::Size | QDir::Reversed);
    picturedir.setSorting(QDir::Name);
    picturedir.setFilter(QDir::Files);

    pictureinfolist = picturedir.entryInfoList();
    for (int cnt = 0, ccnt = 0; cnt < pictureinfolist.size(); cnt++)
    {
        pictureinfo = pictureinfolist.at(cnt);
        QString filesuffix;
        filesuffix = pictureinfo.suffix();
        /**/
        if ((filesuffix == "bmp")  ||
            (filesuffix == "jpg")  ||
            (filesuffix == "jpeg") ||
            (filesuffix == "png")  ||
            (filesuffix == "tga")  ||
            (filesuffix == "gif")  ||
            (filesuffix == "tiff"))
        {
            ui->piclistWidget->addItem(new QListWidgetItem(QIcon(picturechddirpath + "/" + pictureinfo.fileName()), pictureinfo.fileName()));
            //rcnt removes void lists
            QListWidgetItem *item = ui->piclistWidget->item(ccnt++);
            item->setSizeHint(QSize(92, 100));
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->piclistWidget->setIconSize(QSize(92, 80));
    ui->piclistWidget->setSpacing(1);
    ui->piclistWidget->setGridSize(QSize(92, 100));
    ui->piclistWidget->setCurrentItem(ui->videolistWidget->item(0));
    ui->piclistWidget->setCurrentRow(0);

    picturefileName = ui->piclistWidget->item(0)->text();
    picturepath = picturechddirpath + "/" + picturefileName;

    pictureImg.load(picturepath);

    QSize picture = resizepicture(QSize(pictureImg.width(), pictureImg.height()), QSize(920, 770));

    ui->piclabel->setGeometry(60 + 460 - picture.width() / 2, 100 + 385 - picture.height() / 2, picture.width(), picture.height());
    ui->piclabel->setPixmap(QPixmap::fromImage(pictureImg));
    ui->piclabel->setScaledContents(true);
    ui->piclabel->setAlignment(Qt::AlignCenter);

    //network page
     ui->nettableWidget->verticalHeader()->setVisible(false);
     ui->nettableWidget->horizontalHeader()->setVisible(false);
     ui->nettableWidget->setFrameShape(QFrame::NoFrame);
     ui->nettableWidget->setShowGrid(false);
     ui->nettableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->nettableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
     ui->nettableWidget->setColumnWidth(0, 225);
     ui->nettableWidget->setColumnWidth(1, 225);
     ui->nettableWidget->setColumnWidth(2, 225);
     ui->nettableWidget->setColumnWidth(3, 225);
     ui->nettableWidget->setRowHeight(0, 180);
     ui->nettableWidget->setRowHeight(1, 180);
     ui->nettableWidget->setRowHeight(2, 180);
     ui->nettableWidget->setRowHeight(3, 180);
     ui->nettableWidget->setRowHeight(4, 180);
     ui->nettableWidget->setStyleSheet("color:#d4d4d4; background-color:#424242;");
     ui->nettableWidget->setFont(QFont("San Serif", 18));
     QGraphicsDropShadowEffect *nettableWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
     nettableWidget_shadoweffect->setOffset(0, 0);
     nettableWidget_shadoweffect->setColor("#000000");
     nettableWidget_shadoweffect->setBlurRadius(30);
     ui->nettableWidget->setGraphicsEffect(nettableWidget_shadoweffect);

     ui->nettableWidget->setItem(0, 0, new QTableWidgetItem(tr("CCTV 综合")));
     ui->nettableWidget->setItem(0, 1, new QTableWidgetItem(tr("CCTV 财经")));
     ui->nettableWidget->setItem(0, 2, new QTableWidgetItem(tr("CCTV 综艺")));
     ui->nettableWidget->setItem(0, 3, new QTableWidgetItem(tr("CCTV 亚洲")));
     ui->nettableWidget->setItem(1, 0, new QTableWidgetItem(tr("CCTV 体育")));
     ui->nettableWidget->setItem(1, 1, new QTableWidgetItem(tr("CCTV 电影")));
     ui->nettableWidget->setItem(1, 2, new QTableWidgetItem(tr("CCTV 军事农业")));
     ui->nettableWidget->setItem(1, 3, new QTableWidgetItem(tr("CCTV 电视剧")));
     ui->nettableWidget->setItem(2, 0, new QTableWidgetItem(tr("CCTV 记录")));
     ui->nettableWidget->setItem(2, 1, new QTableWidgetItem(tr("CCTV 科教")));
     ui->nettableWidget->setItem(2, 2, new QTableWidgetItem(tr("CCTV 新闻")));
     ui->nettableWidget->setItem(2, 3, new QTableWidgetItem(tr("湖南卫视")));
     ui->nettableWidget->setItem(3, 0, new QTableWidgetItem(tr("辽宁卫视")));
     ui->nettableWidget->setItem(3, 1, new QTableWidgetItem(tr("浙江卫视")));
     ui->nettableWidget->setItem(3, 2, new QTableWidgetItem(tr("江苏卫视")));
     ui->nettableWidget->setItem(3, 3, new QTableWidgetItem(tr("广东卫视")));
     ui->nettableWidget->setItem(4, 0, new QTableWidgetItem(tr("北京卫视")));
     ui->nettableWidget->setItem(4, 1, new QTableWidgetItem(tr("天津卫视")));
     ui->nettableWidget->setItem(4, 2, new QTableWidgetItem(tr("凤凰卫视")));
     ui->nettableWidget->setItem(4, 3, new QTableWidgetItem(tr("沈阳新闻")));

     for (int rcnt = 0; rcnt < 5; rcnt++)
     {
         for (int ccnt = 0; ccnt < 4; ccnt++)
         {
            ui->nettableWidget->item(rcnt, ccnt)->setTextAlignment(Qt::AlignCenter);
         }
     }


    //setting page
    ui->buttonbglabel->setStyleSheet("color:#d4d4d4; background-color:#01579b");
    ui->buttonbglabel->setText("");
    QGraphicsDropShadowEffect *buttonbglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    buttonbglabel_shadoweffect->setOffset(0, 0);
    buttonbglabel_shadoweffect->setColor("#000000");
    buttonbglabel_shadoweffect->setBlurRadius(30);
    ui->buttonbglabel->setGraphicsEffect(buttonbglabel_shadoweffect);

    ui->cpuinfobglabel->setStyleSheet("color:#d4d4d4; background-color:#0288d1");
    ui->cpuinfobglabel->setText("");
    QGraphicsDropShadowEffect *cpuinfobglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    cpuinfobglabel_shadoweffect->setOffset(0, 0);
    cpuinfobglabel_shadoweffect->setColor("#000000");
    cpuinfobglabel_shadoweffect->setBlurRadius(30);
    ui->cpuinfobglabel->setGraphicsEffect(cpuinfobglabel_shadoweffect);

    ui->cpuinfotitlelabel->setStyleSheet("color:#d4d4d4; background-color:#0288d1");
    ui->cpuinfotitlelabel->setText("CPU:\n\n内存:\n\n硬盘:");
    ui->cpuinfotitlelabel->setFont(QFont("San Serif", 14));

    ui->cpuinfoprogressBar->setStyleSheet("color:#424242; background: #e1f5fe");
    ui->cpuinfoprogressBar->setRange(0, 100);

    ui->meminfoprogressBar->setStyleSheet("color:#424242; background: #e1f5fe");
    ui->meminfoprogressBar->setRange(0, 100);

    ui->hdinfoprogressBar->setStyleSheet("color:#424242; background: #e1f5fe");
    ui->hdinfoprogressBar->setRange(0, 100);

    ui->poweroffButton->setStyleSheet("color:#424242; background-color:#01579b");
    ui->poweroffButton->setText("");
    ui->poweroffButton->setIcon(QIcon(":/system/src/poweroff.png"));
    QGraphicsDropShadowEffect *poweroffButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    poweroffButton_shadoweffect->setOffset(0, 0);
    poweroffButton_shadoweffect->setColor("#01579b");
    poweroffButton_shadoweffect->setBlurRadius(20);
    ui->poweroffButton->setGraphicsEffect(poweroffButton_shadoweffect);

    ui->rebootButton->setStyleSheet("color:#d4d4d4; background-color:#01579b");
    ui->rebootButton->setText("");
    ui->rebootButton->setIcon(QIcon(":/system/src/reboot.png"));
    QGraphicsDropShadowEffect *rebootButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    rebootButton_shadoweffect->setOffset(0, 0);
    rebootButton_shadoweffect->setColor("#01579b");
    rebootButton_shadoweffect->setBlurRadius(20);
    ui->rebootButton->setGraphicsEffect(rebootButton_shadoweffect);

    ui->settingbglabel->setStyleSheet("background-color:#757575");
    ui->settingbglabel->setText("");
    QGraphicsDropShadowEffect *settingbglabel_shadoweffect = new QGraphicsDropShadowEffect(this);
    settingbglabel_shadoweffect->setOffset(0, 0);
    settingbglabel_shadoweffect->setColor("#000000");
    settingbglabel_shadoweffect->setBlurRadius(30);
    ui->settingbglabel->setGraphicsEffect(settingbglabel_shadoweffect);

    ui->settingtitletableWidget->verticalHeader()->setVisible(false);
    ui->settingtitletableWidget->horizontalHeader()->setVisible(false);
    ui->settingtitletableWidget->setFrameShape(QFrame::NoFrame);
    ui->settingtitletableWidget->setShowGrid(false);
    ui->settingtitletableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->settingtitletableWidget->setColumnWidth(0, 300);
    ui->settingtitletableWidget->setRowHeight(0, 100);
    ui->settingtitletableWidget->setRowHeight(1, 100);
    ui->settingtitletableWidget->setRowHeight(2, 100);
    ui->settingtitletableWidget->setRowHeight(3, 100);
    ui->settingtitletableWidget->setStyleSheet("color:#d4d4d4; background-color:#424242;");
    ui->settingtitletableWidget->setFont(QFont("San Serif", 16));
    QGraphicsDropShadowEffect *settingtitletableWidget_shadoweffect = new QGraphicsDropShadowEffect(this);
    settingtitletableWidget_shadoweffect->setOffset(0, 0);
    settingtitletableWidget_shadoweffect->setColor("#000000");
    settingtitletableWidget_shadoweffect->setBlurRadius(30);
    ui->settingtitletableWidget->setGraphicsEffect(settingtitletableWidget_shadoweffect);

    ui->settingtitletableWidget->setItem(0, 0, new QTableWidgetItem(tr("      天气预报城市")));
    ui->settingtitletableWidget->setItem(0, 1, new QTableWidgetItem(tr("      视频目录")));
    ui->settingtitletableWidget->setItem(0, 2, new QTableWidgetItem(tr("      视频缩略图目录")));
    ui->settingtitletableWidget->setItem(0, 3, new QTableWidgetItem(tr("      图片目录")));

    ui->settingnoselectlabel->setText("");
    ui->settingnoselectlabel->setStyleSheet("background:transparent");

    ui->citylineEdit->setText(city);
    ui->citylineEdit->setStyleSheet("color:#424242; background-color:#e0e0e0; border-color:#424242");
    ui->citylineEdit->setFont(QFont("San Serif", 12));

    ui->videodirlineEdit->setText(videodirpath);
    ui->videodirlineEdit->setStyleSheet("color:#424242; background-color:#e0e0e0; border-color:#424242");
    ui->videodirlineEdit->setFont(QFont("San Serif", 12));

    ui->videosnapdirlineEdit->setText(videofrmsdirpath);
    ui->videosnapdirlineEdit->setStyleSheet("color:#424242; background-color:#e0e0e0; border-color:#424242");
    ui->videosnapdirlineEdit->setFont(QFont("San Serif", 12));

    ui->picturedirlineEdit->setText(picturedirpath);
    ui->picturedirlineEdit->setStyleSheet("color:#424242; background-color:#e0e0e0; border-color:#424242");
    ui->picturedirlineEdit->setFont(QFont("San Serif", 12));

    ui->settingsaveButton->setStyleSheet("color:#d4d4d4; background-color:#616161");
    ui->settingsaveButton->setText("");
    ui->settingsaveButton->setIcon(QIcon(":/system/src/ok.png"));
    QGraphicsDropShadowEffect *settingsaveButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    settingsaveButton_shadoweffect->setOffset(0, 0);
    settingsaveButton_shadoweffect->setColor("#757575");
    settingsaveButton_shadoweffect->setBlurRadius(20);
    ui->settingsaveButton->setGraphicsEffect(settingsaveButton_shadoweffect);

    ui->settingredoButton->setStyleSheet("color:#d4d4d4; background-color:#616161");
    ui->settingredoButton->setText("");
    ui->settingredoButton->setIcon(QIcon(":/system/src/redo.png"));
    QGraphicsDropShadowEffect *settingredoButton_shadoweffect = new QGraphicsDropShadowEffect(this);
    settingredoButton_shadoweffect->setOffset(0, 0);
    settingredoButton_shadoweffect->setColor("#757575");
    settingredoButton_shadoweffect->setBlurRadius(20);
    ui->settingredoButton->setGraphicsEffect(settingredoButton_shadoweffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sidebarlistWidget_clicked(const QModelIndex &index)
{
    int sidebarNum = index.row();

    ui->mainstackedWidget->setCurrentIndex(sidebarNum);

    switch (sidebarNum)
    {
    case MAINSW_STARTPAGE:
    {
        QString url = weatherURL + city;
        manager->get(QNetworkRequest(QUrl(url)));

        ui->startpage->show();
    }break;
    case MAINSW_VIDEOPAGE:
    {
        ui->videorefreshButton->click();
        ui->videopage->show();
    }break;
    case MAINSW_PICTUREPAGE:
        ui->picturepage->show();
        break;
    case MAINSW_NETPAGE:
        ui->netpage->show();
        break;
    case MAINSW_SETTINGPAGE:
        ui->settingpage->show();
        break;
    default:
        ;
    }
}


void MainWindow::qtimer_timeout_Slot()
{
    int currentpage = ui->mainstackedWidget->currentIndex();

    if (currentpage == MAINSW_SETTINGPAGE)
    {
        ui->cpuinfoprogressBar->setValue(calculateCPUusage());
        ui->meminfoprogressBar->setValue(calculatememusage());
        ui->hdinfoprogressBar->setValue(calculatedisksage());
    }
}

void MainWindow::replayFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString result = QString::fromLocal8Bit(bytes);
        //city = "沈阳";
        //QString url = weatherURL + city;
        //manager->get(QNetworkRequest(QUrl(url)));
        parseXml(result);
    }
    else
    {
        QMessageBox::information(this, tr("网络错误"), tr("请检查网络连接"), QMessageBox::Ok, QMessageBox::Ok);
    }
}

//weather now in xml
void MainWindow::parseXml(QString Xml)
{
    QXmlStreamReader xml(Xml);
/**/
    while(!xml.atEnd())
    {
        if(xml.hasError())
        {
            QMessageBox::information(this, tr("数据错误"), tr("请联系管理员"), QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        else if(xml.isStartElement())
        {
            if(xml.name() == "city")
            {
                weathernow.city = xml.readElementText();
            }
            else if(xml.name() == "updatetime")
            {
                weathernow.updatetime = xml.readElementText();
            }
            else if(xml.name() == "wendu")
            {
                weathernow.temperature = xml.readElementText();
            }
            else if(xml.name() == "fengli")
            {
                weathernow.windpow = xml.readElementText();
            }
            else if(xml.name() == "shidu")
            {
                weathernow.humidity = xml.readElementText();
            }
            else if(xml.name() == "fengxiang")
            {
                weathernow.winddir = xml.readElementText();
            }
            else if(xml.name() == "environment")
            {
                while (xml.name() != "time")
                {
                    xml.readNext();
                    if (xml.name() == "aqi")
                    {
                        weathernow.AQI = xml.readElementText();
                    }
                    else if (xml.name() == "pm25")
                    {
                        weathernow.PM25 = xml.readElementText();
                    }
                    else if (xml.name() == "quality")
                    {
                        weathernow.airquality = xml.readElementText();
                    }
                }
            }
            else if (xml.name()=="forecast")
            {
                if (xml.name() != "weather")
                {
                    for (int cnt = 0; cnt < 5; cnt++)
                    {
                        while (xml.name() != "night")
                        {
                            xml.readNext();
                            if (xml.name() == "date")
                            {
                                weathernow.weatherforecast[cnt].date = xml.readElementText();
                            }
                            else if (xml.name() == "high")
                            {
                                weathernow.weatherforecast[cnt].tempmax = xml.readElementText();
                            }
                            else if (xml.name() == "low")
                            {
                                weathernow.weatherforecast[cnt].tempmin = xml.readElementText();
                            }
                            else if (xml.name() == "type")
                            {
                                weathernow.weatherforecast[cnt].type = xml.readElementText();
                            }
                        }
                        while (xml.name() != "weather")
                        {
                            xml.readNext();
                        }
                    }
                }

                break;
            }
            else
            {
                xml.readNext();
            }
        }
        else
        {
            xml.readNext();
        }
    }

    //ui->weatherbglabel->setText(weathernow.weatherforecast[0].date + weathernow.weatherforecast[0].type + weathernow.weatherforecast[0].winddir);
    ui->citylabel->setText(weathernow.city);
    ui->tempnowlabel->setText(weathernow.temperature + "°");
    ui->weatherpiclabel->setPixmap(QPixmap(":/weather/src/" + weathernow.weatherforecast[0].type + ".png"));

    bool ok;
    QString weatherAQIlevel;
    int weatherAQI = weathernow.AQI.toInt(&ok, 10);
    if (weatherAQI <= 50)
    {
        weatherAQIlevel ="优";
    }
    else if (weatherAQI <= 100)
    {
        weatherAQIlevel ="良";
    }
    else if (weatherAQI <= 150)
    {
        weatherAQIlevel ="轻度污染";
    }
    else if (weatherAQI <= 200)
    {
        weatherAQIlevel ="中度污染";
    }
    else if (weatherAQI <= 300)
    {
        weatherAQIlevel ="中毒污染";
    }
    else
    {
        weatherAQIlevel ="严重污染";
    }

    ui->AQIlabel->setText("AQI: " + weathernow.AQI + "  " + weatherAQIlevel + "\n" "PM2.5: " + weathernow.PM25);
    ui->weatherlabel->setText(weathernow.weatherforecast[0].type);
    ui->weatherinfolabel->setText(weathernow.weatherforecast[0].tempmin.mid(2) + "/" + weathernow.weatherforecast[0].tempmax.mid(2) + "    " + \
                              weathernow.winddir + " " + weathernow.windpow);

    for (int cnt = 0; cnt < 4; cnt++)
    {
        ui->weathertableWidget->setItem(cnt, 0, new QTableWidgetItem(weathernow.weatherforecast[cnt + 1].date.right(3)));
        ui->weathertableWidget->setItem(cnt, 1, new QTableWidgetItem(weathernow.weatherforecast[cnt + 1].type));
        ui->weathertableWidget->setItem(cnt, 2, new QTableWidgetItem(weathernow.weatherforecast[cnt + 1].tempmin.mid(2) + "/" + weathernow.weatherforecast[cnt + 1].tempmax.mid(2)));
        ui->weathertableWidget->item(cnt, 0)->setTextAlignment(Qt::AlignCenter);
    }

    xml.clear();
}

/*
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QString str="("+QString::number(event->x())+","+QString::number(event->y())+")";
    QPoint mousePos = event->globalPos();
    QString mp = QString::number(mousePos.x(), 10) + QString::number(mousePos.y(), 10);

    ui->lineEdit->setText(str);

    int sidebarmposcnt = 0;

    if (mousePos.x() <= 240)
    {
        if (mousePos.y() <= 80)
        {
            sidebarmposcnt = 1;
        }
        else if (mousePos.y() <= 160)
        {
            sidebarmposcnt = 2;
        }
        else if (mousePos.y() <= 240)
        {
            sidebarmposcnt = 3;
        }
        else if (mousePos.y() <= 320)
        {
            sidebarmposcnt = 4;
        }
        else if (mousePos.y() <= 400)
        {
            sidebarmposcnt = 5;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }

    int sidebarcurcnt = ui->sidebarlistWidget->currentRow();
    if (sidebarcurcnt != (sidebarmposcnt - 1))
    {
        QListWidgetItem *item = ui->sidebarlistWidget->item(sidebarmposcnt - 1);
        item->setBackgroundColor("#1c3e5c");
    }
}
*/

void MainWindow::on_videolistWidget_clicked(const QModelIndex &index)
{
    videofileName = ui->videolistWidget->item(index.row())->text();

    QString videoinfotitle = "上次观看：";
    videoinfo.setFile(videodirpath, videofileName);
    QDateTime time = videoinfo.lastRead();
    ui->videoinfolabel->setText(videoinfotitle + time.toString("yyyy/MM/dd hh:mm:ss"));

    QString filesuffix = videoinfo.suffix();
    if ((filesuffix == "mkv")  ||
        (filesuffix == "avi")  ||
        (filesuffix == "mp4")  ||
        (filesuffix == "flv"))
    {
        videofrmspath = videofrmsdirpath + "/" + videoinfo.fileName();
        videosnpImg.load(videofrmspath);
        ui->videosnaplabel->setPixmap(QPixmap::fromImage(videosnpImg));
        ui->videosnaplabel->setScaledContents(true);
        ui->videosnaplabel->resize(ui->videosnaplabel->width(), ui->videosnaplabel->height());
    }
    else  if ((filesuffix == "rm")     ||
                 (filesuffix == "rmvb"))
    {
        ui->videosnaplabel->setStyleSheet("color:#d4d4d4");
        ui->videosnaplabel->setFont(QFont("San Serif", 12));
        ui->videosnaplabel->setAlignment(Qt::AlignCenter);
        ui->videosnaplabel->setText("rm/rmvb格式可能会存在卡顿");
    }
}


void MainWindow::qtimer_textscrolling_Slot(void)
{
    static int videonamelabelPos = 0, lastvideonameSelected = 0, displaydelayCnt = 0;

    if (ui->videolistWidget->currentRow() != lastvideonameSelected)
    {
        videonamelabelPos = 0;

        //lastvideonameSelected = ui->videolistWidget->currentRow();
        displaydelayCnt = 0;
    }

    if (ui->mainstackedWidget->currentIndex() == MAINSW_VIDEOPAGE)
    {
        QString videofileName= ui->videolistWidget->currentItem()->text();

        if (videofileName.length() > 26)
        {
            //if (videonamelabelPos > videofileName.length())
            if (videonamelabelPos > (videofileName.length() - 18))
            {
                videonamelabelPos = 0;
                displaydelayCnt = 0;
            }
            ui->videonamelabel->setText(videofileName.mid(videonamelabelPos));

            displaydelayCnt ++;
            if (displaydelayCnt > 2)
            {
                videonamelabelPos++;
            }

            lastvideonameSelected = ui->videolistWidget->currentRow();
        }
        else
        {
            ui->videonamelabel->setText(ui->videolistWidget->currentItem()->text());
        }
    }
}

void MainWindow::on_videoplayButton_clicked()
{
    videofileName = ui->videolistWidget->currentItem()->text();
    videoinfo.setFile(videodirpath, videofileName);
    videopath = videodirpath + "/" + videoinfo.fileName();

    QString videoprgm, filesuffix;
    QStringList videoargm;
    filesuffix = videoinfo.suffix();

    if ((filesuffix == "mkv")  ||
        (filesuffix == "avi")  ||
        (filesuffix == "mp4")  ||
        (filesuffix == "flv"))
    {
        videoprgm = "xterm";
        //videoargm << "-e" << "omxplayer" << "-b" << "--blank" << videopath;
        //videoprgm = "omxplayer";
       videoargm << "-e" << "omxplayer" << "-r" << "-o" << "hdmi" << videopath;
       //videoprgm = "mplayer";
       //videoargm <<"-fs"<< videopath;
    }
    else  if ((filesuffix == "rm")     ||
                 (filesuffix == "rmvb"))
    {
        videoprgm = "mplayer";
        videoargm <<"-fs"<< videopath;
        //videoprgm = "xterm";
        //videoargm << "-fullscreen" << "-fg" << "black" << "-bg" << "black" << "-e" << "mplayer" << "-fs" << videopath;
    }

    QProcess *ffmpeg_prcs = new QProcess(this);

    ffmpeg_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    ffmpeg_prcs->setReadChannel(QProcess::StandardOutput);
    ffmpeg_prcs->start(videoprgm, videoargm);
    ffmpeg_prcs->waitForFinished();
    //ffmpeg_prcs->close();
}

void MainWindow::on_videodeleteButton_clicked()
{
    videofileName = ui->videolistWidget->currentItem()->text();
    videoinfo.setFile(videodirpath, videofileName);
    videopath = videodirpath + "/" + videoinfo.fileName();

    QStringList videoargm;
    QString videoprgm = "rm";
    videoargm << videopath;

    QProcess *rm_prcs = new QProcess(this);
    rm_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    rm_prcs->setReadChannel(QProcess::StandardOutput);
    rm_prcs->start(videoprgm, videoargm);
    rm_prcs->waitForFinished();
    rm_prcs->close();

    ui->videolistWidget->clear();

    //QDir videodir;
    videodir.setPath(videodirpath);
    videodir.setSorting(QDir::DirsFirst | QDir::Time);
    videodir.setFilter(QDir::Files);

    videinfolist = videodir.entryInfoList();

    for (int cnt = 0, rcnt = 0; cnt < videinfolist.size(); ++cnt)
    {
        videoinfo = videinfolist.at(cnt);

        QString filesuffix;
        filesuffix = videoinfo.suffix();

        if ((filesuffix == "")     ||
            (filesuffix == "mkv")  ||
            (filesuffix == "avi")  ||
            (filesuffix == "mp4")  ||
            (filesuffix == "rmvb") ||
            (filesuffix == "rm")   ||
            (filesuffix == "flv"))
        {
            ui->videolistWidget->addItem(new QListWidgetItem(videoinfo.fileName()));

            QListWidgetItem *item = ui->videolistWidget->item(rcnt++);
            item->setSizeHint(QSize(item->sizeHint().width(), 36));
            item->setTextAlignment(Qt::AlignLeft);
        }
    }
    ui->videolistWidget->setCurrentRow(0);
}

void MainWindow::on_videorefreshButton_clicked()
{
    videofileName = ui->videolistWidget->currentItem()->text();
    videoinfo.setFile(videodirpath, videofileName);

    ui->videolistWidget->clear();

    videodir.setPath(videodirpath);
    videodir.setSorting(QDir::DirsFirst | QDir::Time);
    videodir.setFilter(QDir::Files);

    videinfolist = videodir.entryInfoList();

    for (int cnt = 0, rcnt = 0; cnt < videinfolist.size(); ++cnt)
    {
        videoinfo = videinfolist.at(cnt);

        QString filesuffix;
        filesuffix = videoinfo.suffix();

        if ((filesuffix == "")     ||
            (filesuffix == "mkv")  ||
            (filesuffix == "avi")  ||
            (filesuffix == "mp4")  ||
            (filesuffix == "rmvb") ||
            (filesuffix == "rm")   ||
            (filesuffix == "flv"))
        {
            ui->videolistWidget->addItem(new QListWidgetItem(videoinfo.fileName()));

            QListWidgetItem *item = ui->videolistWidget->item(rcnt++);
            item->setSizeHint(QSize(item->sizeHint().width(), 36));
            item->setTextAlignment(Qt::AlignLeft);
        }
    }
    ui->videolistWidget->setCurrentRow(0);
}

void MainWindow::on_piclistWidget_clicked(const QModelIndex &index)
{
    picturefileName = ui->piclistWidget->item(index.row())->text();
    picturepath = picturechddirpath + "/" + picturefileName;

    pictureImg.load(picturepath);

    QSize picture = resizepicture(QSize(pictureImg.width(), pictureImg.height()), QSize(920, 770));

    ui->piclabel->setGeometry(60 + 460 - picture.width() / 2, 100 + 385 - picture.height() / 2, picture.width(), picture.height());
    ui->piclabel->setPixmap(QPixmap::fromImage(pictureImg));
    ui->piclabel->setScaledContents(true);
    ui->piclabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_picdirlistWidget_clicked(const QModelIndex &index)
{
    picturechddirpath = picturedirpath + "/" +ui->picdirlistWidget->item(index.row())->text();

    ui->piclistWidget->clear();

    picturedir.setPath(picturechddirpath);
    //tdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    //videodir.setSorting(QDir::DirsFirst | QDir::Size | QDir::Reversed);
    picturedir.setSorting(QDir::Name | QDir::Time);
    picturedir.setFilter(QDir::Files);

    pictureinfolist = picturedir.entryInfoList();
    int ccnt = 0;
    for (int cnt = 0; cnt < pictureinfolist.size(); cnt++)
    {
        pictureinfo = pictureinfolist.at(cnt);
        QString filesuffix;
        filesuffix = pictureinfo.suffix();
        /**/
        if ((filesuffix == "bmp")  ||
            (filesuffix == "jpg")  ||
            (filesuffix == "jpeg") ||
            (filesuffix == "png")  ||
            (filesuffix == "tga")  ||
            (filesuffix == "gif")  ||
            (filesuffix == "tiff"))
        {
            ui->piclistWidget->addItem(new QListWidgetItem(QIcon(picturechddirpath + "/" + pictureinfo.fileName()), pictureinfo.fileName()));
            //rcnt removes void lists
            QListWidgetItem *item = ui->piclistWidget->item(ccnt++);
            item->setSizeHint(QSize(92, 100));
            item->setTextAlignment(Qt::AlignCenter);
        }
    }

    if (ccnt > 0)
    {
        ui->piclistWidget->setCurrentRow(0);

        picturefileName = ui->piclistWidget->item(0)->text();
        picturepath = picturechddirpath + "/" + picturefileName;

        pictureImg.load(picturepath);

        QSize picture = resizepicture(QSize(pictureImg.width(), pictureImg.height()), QSize(920, 770));

        ui->piclabel->setGeometry(60 + 460 - picture.width() / 2, 100 + 385 - picture.height() / 2, picture.width(), picture.height());
        ui->piclabel->setPixmap(QPixmap::fromImage(pictureImg));
        ui->piclabel->setScaledContents(true);
        ui->piclabel->setAlignment(Qt::AlignCenter);
    }
}


QSize MainWindow::resizepicture(QSize picturesize, QSize labelsize)
{
    float picwidth, picheight;

    if (picturesize.width() > picturesize.height())
    {
        if (picturesize.width() > labelsize.width())
        {
            picwidth = labelsize.width();
            picheight = picturesize.height() * labelsize.width() / picturesize.width();
        }
        else
        {
            picwidth = picturesize.width();
            picheight = picturesize.height();
        }
    }
    else
    {
        if (picturesize.height() > labelsize.height())
        {
            picheight = labelsize.height();
            picwidth = picturesize.width() * labelsize.height() / picturesize.height();
        }
        else
        {
            picwidth = picturesize.width();
            picheight = picturesize.height();
        }
    }

    return QSize(picwidth, picheight);
}

int MainWindow::calculateCPUusage(void)
{
    //method A of cpu usage calculating
    QByteArray cpuinfobytearray;
    QString cpuinfoprgm = "cat";
    QStringList cpuinfoargm;
    cpuinfoargm << "/proc/stat";
    QProcess *cpuinfo_prcs = new QProcess(this);
    cpuinfo_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    cpuinfo_prcs->setReadChannel(QProcess::StandardOutput);

    cpuinfo_prcs->readAllStandardOutput();

    cpuinfo_prcs->start(cpuinfoprgm, cpuinfoargm);
    cpuinfo_prcs->waitForReadyRead();
    cpuinfobytearray = cpuinfo_prcs->readAll();

    //cpuinfo_prcs->waitForFinished();
    cpuinfo_prcs->close();

    QString cpuinfostr(cpuinfobytearray);
    QStringList cpuinfolist = cpuinfostr.split(" ");
    cpuinfo_def cpuinfo;

    static float lastcputotletime = 0, lastidletime = 0;

    float cputotletime = 0, cpuusage = 0;
    for (int cnt = 0; cnt < 9; cnt ++)
    {
        cpuinfo.frame[cnt] = cpuinfolist.at(cnt + 2).toInt();
        cputotletime += (float)cpuinfo.frame[cnt];
    }

    cpuusage = 100 - 100 * (cpuinfo.members.idle - lastidletime) / (cputotletime - lastcputotletime);

    lastcputotletime = cputotletime;
    lastidletime = cpuinfo.members.idle;

    return (int)cpuusage ;

    /*
    //method B of cpu usage calculating
    QByteArray cpuinfostr;
    QString cpuinfoprgm = "top";
    QStringList cpuinfoargm;
    cpuinfoargm << "-n" << "2";
    QProcess *cpuinfo_prcs = new QProcess(this);
    cpuinfo_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    cpuinfo_prcs->setReadChannel(QProcess::StandardOutput);
    cpuinfo_prcs->readAllStandardOutput();

    cpuinfo_prcs->start(cpuinfoprgm, cpuinfoargm);
    cpuinfo_prcs->waitForReadyRead();
    cpuinfostr = cpuinfo_prcs->readAll();

    cpuinfo_prcs->waitForFinished();
    cpuinfo_prcs->close();

    ui->settingbglabel->setText(cpuinfostr);

    return 0;
*/
}

int MainWindow::calculatememusage(void)
{
    QByteArray meminfobytearray;
    QString meminfoprgm = "free";
    QStringList meminfoargm;
    meminfoargm << "-m";
    QProcess *meminfo_prcs = new QProcess(this);
    meminfo_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    meminfo_prcs->setReadChannel(QProcess::StandardOutput);
    meminfo_prcs->readAllStandardOutput();

    meminfo_prcs->start(meminfoprgm, meminfoargm);
    meminfo_prcs->waitForReadyRead();
    meminfobytearray = meminfo_prcs->readAll();

    meminfo_prcs->waitForFinished();
    meminfo_prcs->close();

    QString meminfostr(meminfobytearray);
    QStringList meminfolist = meminfostr.split("        ");

    float memusage = 0;
    memusage = 100 * meminfolist.at(5).toFloat() / meminfolist.at(4).toFloat();

    return memusage;
}


int MainWindow::calculatedisksage(void)
{
    QByteArray diskinfobytearray;
    QString diskinfoprgm = "df";
    QStringList diskinfoargm;
    diskinfoargm << "-h" << "/dev/sda1";
    QProcess *diskinfo_prcs = new QProcess(this);
    diskinfo_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    diskinfo_prcs->setReadChannel(QProcess::StandardOutput);
    diskinfo_prcs->readAllStandardOutput();

    diskinfo_prcs->start(diskinfoprgm, diskinfoargm);
    diskinfo_prcs->waitForReadyRead();
    diskinfobytearray = diskinfo_prcs->readAll();

    diskinfo_prcs->waitForFinished();
    diskinfo_prcs->close();

    QString diskinfostr(diskinfobytearray);
    QStringList diskinfolist = diskinfostr.split("   ");

    int diskusage = 0;
    diskusage = diskinfolist.at(5).left(2).toInt();

    return diskusage;
}


void MainWindow::on_poweroffButton_clicked()
{
    QString poweroffprgm = "poweroff";

    QProcess *poweroff_prcs = new QProcess(this);
    poweroff_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    poweroff_prcs->setReadChannel(QProcess::StandardOutput);
    poweroff_prcs->start(poweroffprgm);
    poweroff_prcs->waitForFinished();
    poweroff_prcs->close();
}

void MainWindow::on_rebootButton_clicked()
{
    QString rebootprgm = "reboot";

    QProcess *poweroff_prcs = new QProcess(this);
    poweroff_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    poweroff_prcs->setReadChannel(QProcess::StandardOutput);
    poweroff_prcs->start(rebootprgm);
    poweroff_prcs->waitForFinished();
    poweroff_prcs->close();
}

void MainWindow::on_settingsaveButton_clicked()
{
    city = ui->citylineEdit->text();
    videodirpath = ui->videodirlineEdit->text();
    videofrmsdirpath = ui->videosnapdirlineEdit->text();
    picturedirpath = ui->picturedirlineEdit->text();
}



void MainWindow::on_settingredoButton_clicked()
{
    QString admincode = "";
    admincode = ui->videodirlineEdit->text();
    if (admincode == "letmeout")
    {
        QApplication::exit();
    }
    else
    {

        city = DEFAULTCITY;
        videodirpath = VIDEODIR_PATH;
        videofrmsdirpath = VIDEOSNAPDIR_PATH;
        picturedirpath = PICTUREDIR_PATH;

        ui->citylineEdit->setText(city);
        ui->videodirlineEdit->setText(videodirpath);
        ui->videosnapdirlineEdit->setText(videofrmsdirpath);
        ui->picturedirlineEdit->setText(picturedirpath);
    }
}


void MainWindow::on_nettableWidget_doubleClicked(const QModelIndex &index)
{
    QStringList netvideoargm;
    QString netvideoprgm;
    QString netvideopath;

    switch (index.row())
    {
    case 0:
    {
        switch (index.column())
        {
        case 0:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv1.m3u8";
            break;
        case 1:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv2.m3u8";
            break;
        case 2:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv3.m3u8";
            break;
        case 3:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv4.m3u8";
            break;
        }
    }break;
    case 1:
    {
        switch (index.column())
        {
        case 0:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv5.m3u8";
            break;
        case 1:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv6.m3u8";
            break;
        case 2:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv7.m3u8";
            break;
        case 3:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv8.m3u8";
            break;
        }
    }break;
    case 2:
    {
        switch (index.column())
        {
        case 0:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv9.m3u8";
            break;
        case 1:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv10.m3u8";
            break;
        case 2:
            netvideopath = "http://ivi.bupt.edu.cn/hls/cctv13.m3u8";
            break;
        case 3:
            netvideopath = "http://ivi.bupt.edu.cn/hls/hunanhd.m3u8";
            break;
        }
    }break;
    case 3:
    {
        switch (index.column())
        {
        case 0:
            netvideopath = "http://ivi.bupt.edu.cn/hls/lnhd.m3u8";
            break;
        case 1:
            netvideopath = "http://ivi.bupt.edu.cn/hls/zjhd.m3u8";
            break;
        case 2:
            netvideopath = "http://ivi.bupt.edu.cn/hls/jshd.m3u8";
            break;
        case 3:
            netvideopath = "http://ivi.bupt.edu.cn/hls/gdhd.m3u8";
            break;
        }
    }break;
    case 4:
    {
        switch (index.column())
        {
        case 0:
            netvideopath = "http://ivi.bupt.edu.cn/hls/btvhd.m3u8";
            break;
        case 1:
            netvideopath = "http://ivi.bupt.edu.cn/hls/tjhd.m3u8";
            break;
        case 2:
            netvideopath = "http://live.3gv.ifeng.com/live/FHZXHD.m3u8";
            break;
        case 3:
            netvideopath = "http://streamer.csytv.com/live/1?fmt=H264_800K_FLV";
            break;
        }
    }break;
    default:
    {
        break;
    }
    }

    netvideoprgm = "xterm";
    netvideoargm << "-e" << "omxplayer" << "-b" << "--blank" << netvideopath;
    //netvideoargm << "-e" << "mplayer" << "-fs" <<  netvideopath;
    //netvideoprgm = "mplayer";
    //netvideoargm << "-fs" << netvideopath;

    QProcess *ffmpeg_prcs = new QProcess(this);
    ffmpeg_prcs->setProcessChannelMode(QProcess::SeparateChannels);
    ffmpeg_prcs->setReadChannel(QProcess::StandardOutput);
    ffmpeg_prcs->start(netvideoprgm, netvideoargm);
    ffmpeg_prcs->waitForFinished();
    //ffmpeg_prcs->close();
}
