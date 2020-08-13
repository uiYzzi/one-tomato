#include "widget.h"
#include "ui_widget.h"
#include<QDateTime>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <sstream>
#include <QString>
#include <DApplication>
using namespace std;
QTimer *timer = new QTimer();
int a;
bool timerswitch;
int ms;
Widget::Widget(DBlurEffectWidget *parent) :
    DBlurEffectWidget(parent),
    m_menu(new QMenu),
    m_5(new QAction("5分钟")),
    m_15(new QAction("15分钟")),
    m_25(new QAction("25分钟")),
    m_35(new QAction("35分钟")),
    m_45(new QAction("45分钟")),


    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->titlebar->setFixedHeight(50);//初始化标题栏
    ui->titlebar->setBackgroundTransparent(true);//设置标题栏透明
    ui->titlebar->setIcon(QIcon::fromTheme(":/icon/icon/top.yzzi.tomato.svg"));
    ui->titlebar->setTitle("");
    setMaskAlpha(190);
    ui->titlebar->setMenu(m_menu);
    ms = 1500;//设置初始时间

    m_menu->addMenu(menu_times);//设置菜单
    menu_times->setTitle(tr("时间"));
    menu_times->addAction(m_5);
    menu_times->addAction(m_15);
    menu_times->addAction(m_25);
    menu_times->addAction(m_35);
    menu_times->addAction(m_45);


    timesGroup = new QActionGroup(this);//设置按钮互斥
    timesGroup->addAction(m_5);
    timesGroup->addAction(m_15);
    timesGroup->addAction(m_25);
    timesGroup->addAction(m_35);
    timesGroup->addAction(m_45);

    m_5->setCheckable(true);
    m_15->setCheckable(true);
    m_25->setCheckable(true);
    m_35->setCheckable(true);
    m_45->setCheckable(true);

    m_25->setChecked(true);

    //设置按钮响应
    connect(m_5,&QAction::triggered,[=](){ms = 301;timer->start(1000);refresh();});
    connect(m_15,&QAction::triggered,[=](){ms = 901;timer->start(1000);refresh();});
    connect(m_25,&QAction::triggered,[=](){ms = 1501;timer->start(1000);refresh();});
    connect(m_35,&QAction::triggered,[=](){ms = 2101;timer->start(1000);refresh();});
    connect(m_45,&QAction::triggered,[=](){ms = 2701;timer->start(1000);refresh();});


    switchbutton = new DSwitchButton (this);
    ui->horizontalLayout_2->addWidget(switchbutton);
    switchbutton->setChecked(false);
    timerswitch=false;
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    setFixedSize(this->width(),this->height());// 禁止拖动窗口大小
    connect(switchbutton, SIGNAL(checkedChanged(bool)), this, SLOT(onSBtnSwitchButtonCheckedChanged(bool)));
    //时间更新
    timer->start(1000); //每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()), this,SLOT(refresh()));
    refresh();


    //音频播放
    player = new QMediaPlayer;
    player->setVolume(100);
    player->setMedia(QUrl("qrc:/audio/ding.wav"));
}
void Widget::refresh()
{
    ostringstream timeshow;
    if(timerswitch==true)
    {
        ms=ms-1;
        QDateTime tomato_time = QDateTime::fromTime_t(ms);
        QString textout=tomato_time.toString("mm:ss");
        ui->time->setText(textout);
        if(ms==0)
        {
            player->play();
            timer->stop();
        }
    }else {
        QDateTime current_time = QDateTime::currentDateTime();
        QString str=current_time.toString("hh:mm");
        ui->time->setText(str);
    }
}
DTitlebar* Widget::getTitlebar()
{
    return ui->titlebar;
}
Widget::~Widget()
{
    delete ui;
    qDebug()<<"exit";
    DApplication::quit();
}

void Widget::onSBtnSwitchButtonCheckedChanged(bool ck)
{

    if(ck==true)
    {
        timerswitch=true;
        timer->start(1000);
        /*Widget::player->play();*/
    }
    else
    {
        timerswitch=false;
        timer->start(1000);
        /*Widget::player->stop();*/
    }
    refresh();

}


