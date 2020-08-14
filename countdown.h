#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QObject>
#include <QTimer>

class countDown : public QObject
{
    Q_OBJECT
public:
    explicit countDown(QObject *parent = nullptr);
    int ms;//供Widget访问
    bool end=true;//控制是否响应timeout信号
    int mem=ms=1500;
    QTimer *timer;

signals:
    void refreshed();//刷新完成信号
    void ended();//计时结束信号
    void setted();//设置时间完成信号(会和refresh形成死循环，废弃)

public slots:
    void refresh();//刷新
    void setTime(int t);//设置时间(菜是原罪,写不来,暂时废弃)
    void reset();//重置时间
    void start();//开始响应timeout信号
    void stop();//停止响应timeout信号
};

#endif // COUNTDOWN_H
