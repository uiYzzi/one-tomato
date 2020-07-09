#include "widget.h"
#include "ui_widget.h"
#include <ctime>
#include <sstream>
#include <string>

using namespace std;




bool timerswitch;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    switchbutton = new DSwitchButton (this);
    ui->horizontalLayout_2->addWidget(switchbutton);
    switchbutton->setChecked(false);
    timerswitch=false;
    connect(switchbutton, SIGNAL(checkedChanged(bool)), this, SLOT(onSBtnSwitchButtonCheckedChanged(bool)));

}
Widget::~Widget()
{
    delete ui;
}




void Widget::onSBtnSwitchButtonCheckedChanged(bool ck)
{
    if(ck==true)
        timerswitch=true;
    else
        timerswitch=false;

}


