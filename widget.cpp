#include "widget.h"
#include "ui_widget.h"
#include<QDateTime>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <sstream>
#include <QString>
#include <DApplication>
#include <QDialog>
#include <DInputDialog>
#include "countdown.h"
using namespace std;
Widget::Widget(DBlurEffectWidget *parent) :
    DBlurEffectWidget(parent),
    m_menu(new QMenu),
    m_5(new QAction("5分钟")),
    m_15(new QAction("15分钟")),
    m_25(new QAction("25分钟")),
    m_35(new QAction("35分钟")),
    m_45(new QAction("45分钟")),
    m_set(new QAction("自定义时间")),


    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->titlebar->setFixedHeight(50);//初始化标题栏
    ui->titlebar->setBackgroundTransparent(true);//设置标题栏透明
    ui->titlebar->setIcon(QIcon::fromTheme(":/icon/icon/top.yzzi.tomato.svg"));
    ui->titlebar->setTitle("");
    setMaskAlpha(190);
    ui->titlebar->setMenu(m_menu);

    m_menu->addMenu(menu_times);//设置菜单
    menu_times->setTitle(tr("时间"));
    menu_times->addAction(m_5);
    menu_times->addAction(m_15);
    menu_times->addAction(m_25);
    menu_times->addAction(m_35);
    menu_times->addAction(m_45);
    menu_times->addAction(m_set);


    timesGroup = new QActionGroup(this);//设置按钮互斥
    timesGroup->addAction(m_5);
    timesGroup->addAction(m_15);
    timesGroup->addAction(m_25);
    timesGroup->addAction(m_35);
    timesGroup->addAction(m_45);
    timesGroup->addAction(m_set);

    m_5->setCheckable(true);
    m_15->setCheckable(true);
    m_25->setCheckable(true);
    m_35->setCheckable(true);
    m_45->setCheckable(true);
    m_set->setCheckable(true);
    m_25->setChecked(true);
    //in->setParent(this);
    //设置按钮响应
    connect(m_5,&QAction::triggered,[=](){count->mem=count->ms = 300;refresh();});
    connect(m_15,&QAction::triggered,[=](){count->mem=count->ms = 900;refresh();});
    connect(m_25,&QAction::triggered,[=](){count->mem=count->ms = 1500;refresh();});
    connect(m_35,&QAction::triggered,[=](){count->mem=count->ms = 2100;refresh();});
    connect(m_45,&QAction::triggered,[=](){count->mem=count->ms = 2700;refresh();});
    connect(m_set,&QAction::triggered,[=](){input();refresh();});

    //实例化对象
    count=new countDown(this);
    toptime=new topTime(this);

    switchbutton = new DSwitchButton (this);
    ui->horizontalLayout_2->addWidget(switchbutton);
    switchbutton->setChecked(false);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    setFixedSize(this->width(),this->height());// 禁止拖动窗口大小
    connect(switchbutton, SIGNAL(checkedChanged(bool)), this, SLOT(onSBtnSwitchButtonCheckedChanged(bool)));

    //结束时音频播放（待修改！）
     player = new QMediaPlayer(this);
     player->setVolume(100);
     player->setMedia(QUrl("qrc:/audio/ding.wav"));

    //设置界面刷新和对象响应
    connect(count,&countDown::refreshed,this,&Widget::refreshCount);
    connect(toptime,&topTime::refreshed,this,&Widget::refreshTime);
    connect(count,&countDown::ended,player,&QMediaPlayer::play);

    //时间控制
    timer->start(1000); //每隔1000ms发送timeout的信号
    refreshCount();
    refreshTime();
}

void Widget::refresh()//刷新count的开始结束动作
{
    if(btSwitch)
    {
        if(!count->ms) count->reset();
        count->start();
    }
    else
    {
        count->stop();
    }
}
void Widget::refreshTime()//用toptime的信息刷新时间显示
{
    ui->titlebar->setTitle(toptime->str);
}
void Widget::refreshCount()//用count的信息刷新倒计时显示
{
    QDateTime tomato_time = QDateTime::fromTime_t(count->ms);
    QString textout=tomato_time.toString("mm:ss");
    ui->time->setText(textout);
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
void Widget::input()//输入时间
{
    bool isOK;
    int i = DInputDialog::getInt(this, "输入时间",
                                        "请输入时间（分钟，小于60）",
                                        count->mem/60,0,100,1,&isOK);
    if(isOK)
    {
        count->ms=count->mem=60*i;
    }
    switch (count->mem) {
        case 300+1:
            m_5->setChecked(true);
            break;
        case 900+1:
            m_15->setChecked(true);
            break;
        case 1500+1:
            m_25->setChecked(true);
            break;
        case 2100+1:
            m_35->setChecked(true);
            break;
        case 2700+1:
            m_45->setChecked(true);
            break;
    }
}
void Widget::onSBtnSwitchButtonCheckedChanged(bool ck)
{
    player->stop();
    btSwitch=ck;
    refresh();
}
