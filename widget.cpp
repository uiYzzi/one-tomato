#include "widget.h"
#include "ui_widget.h"
#include<QDateTime>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    switchbutton = new DSwitchButton (this);
    ui->horizontalLayout_2->addWidget(switchbutton);
    switchbutton->setChecked(false);
    connect(switchbutton, SIGNAL(checkedChanged(bool)), this, SLOT(onSBtnSwitchButtonCheckedChanged(bool)));
    //时间更新
    QTimer *timer = new QTimer(this);
    timer->start(1000); //每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()), this,SLOT(refresh()));
    refresh();
    //音频播放
    player = new QMediaPlayer;
    player->setVolume(100);
    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile(qApp->applicationDirPath()+"/rain.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);
}
void Widget::refresh()
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString str=current_time.toString("hh:mm");
    ui->time->setText(str);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::onSBtnSwitchButtonCheckedChanged(bool ck)
{

    if(ck==true)
    {
        Widget::player->play();
    }
    else
    {
        Widget::player->stop();
    }

}


