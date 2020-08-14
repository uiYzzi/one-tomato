#include "countdown.h"

countDown::countDown(QObject *parent) : QObject(parent)
{
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&countDown::refresh);
}

void countDown::refresh()
{
    if(ms)
    {
        ms--;
        if(!ms) emit ended();//计时结束,触发结束信号,写在这里是为了让声音和画面同步
    }
    else
    {
        if(timer->isActive())timer->stop();
    }
    emit refreshed();
}

void countDown::setTime(int t)//弃坑,写不来
{
    mem=ms=t;
    emit setted();
}
void countDown::reset()
{
    ms=mem;
    refresh();
    emit setted();
}
void countDown::start()
{
    emit refreshed();
    timer->start(1000);
}
void countDown::stop()
{
    emit refreshed();
    if(timer->isActive())timer->stop();
}
