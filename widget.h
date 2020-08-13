#ifndef WIDGET_H
#define WIDGET_H

#include <dswitchbutton.h>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include <DBlurEffectWidget>
#include <DTitlebar>

DWIDGET_USE_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    explicit Widget(DBlurEffectWidget *parent = 0);
    ~Widget();
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    DTitlebar* getTitlebar();


private slots:
    void onSBtnSwitchButtonCheckedChanged(bool);
    void refresh();


private:
    Ui::Widget *ui;
    DSwitchButton * switchbutton;
    QTimer *timer = new QTimer();
    int a;
    bool timerswitch;
    int ms;
    DTitlebar *titlebar;
    QMenu *m_menu;
    QActionGroup *timesGroup;
    QAction *m_5;
    QAction *m_15;
    QAction *m_25;
    QAction *m_35;
    QAction *m_45;


    QMenu *menu_times=new QMenu;

};

#endif // WIDGET_H
