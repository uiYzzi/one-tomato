#include <DApplication>
#include <QDesktopWidget>
#include <DWidgetUtil>  //Dtk::Widget::moveToCenter(&w); 要调用它，就得引用DWidgetUtil
#include <widget.h>

DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication a(argc, argv);

     a.setAttribute(Qt::AA_UseHighDpiPixmaps);
     a.loadTranslator();
     a.setOrganizationName("deepin");
     a.setApplicationVersion(DApplication::buildVersion("1.0.3"));
     a.setApplicationAcknowledgementPage("https://blog.yzzi.top");
     a.setProductIcon(QIcon(":/icon/icon/top.yzzi.tomato.svg"));  //设置Logo
     a.setProductName("一只番茄");
     a.setApplicationName("一只番茄"); //只有在这儿修改窗口标题才有效
     a.setApplicationDescription("感谢deepin社区 @gbwater 提供的帮助");


    Widget w;
    QDesktopWidget *s=DApplication::desktop();
    w.show();

    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);


    return a.exec();
}
