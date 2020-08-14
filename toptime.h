#ifndef TOPTIME_H
#define TOPTIME_H

#include <QObject>
#include <QDateTime>
#include <QTimer>

class topTime : public QObject
{
    Q_OBJECT
public:
    explicit topTime(QObject *parent = nullptr);
    QString str;//供Widget访问
    QDateTime current_time;
    QTimer *timer;

signals:
    void refreshed();//刷新完成信号
public slots:
    void refresh();//刷新槽函数
};

#endif // TOPTIME_H
