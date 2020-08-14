#include "toptime.h"
#include <QDateTime>

topTime::topTime(QObject *parent) : QObject(parent)
{
    current_time = QDateTime::currentDateTime();
    str=current_time.toString("hh:mm");
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&topTime::refresh);
    timer->start(1000);
}

void topTime::refresh()
{
    current_time = QDateTime::currentDateTime();
    str=current_time.toString("hh:mm");
    emit refreshed();
}
