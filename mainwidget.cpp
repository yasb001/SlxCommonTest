#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDesktopWidget>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    // 设置位置和大小
    setWidgetSizeAndPos();
    // 设置透明度
    setWindowOpacity(0.7);
    // 设置窗口模式
    setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint);

//    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents,true);

    createSystemTrayIcon();

    // 启动计时器更新时间
    startTimer(1000);


}



MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::updateTime()
{

}

void MainWidget::setWidgetSizeAndPos()
{
    setFixedSize(m_Width, m_Height);
    // 获取桌面大小
    QRect desktopSize = getDesktopSize();

    m_Rect.setX(desktopSize.width() - m_Width - m_Spacer);
    m_Rect.setY(m_Spacer);
    m_Rect.setWidth(m_Width);
    m_Rect.setHeight(m_Height);
    move(m_Rect.x(), m_Rect.y());
}



QRect MainWidget::getDesktopSize()
{
    QDesktopWidget *desktop = QApplication::desktop();
    return desktop->screenGeometry();
}


void MainWidget::timerEvent(QTimerEvent *event)
{
    QString time = QTime::currentTime().toString();
    if(m_Rect.contains(QCursor::pos()))
    {
        m_TrayIcon->showMessage("shedule", "sleep", QSystemTrayIcon::Information, 5000);
        hide();
    }
    else
    {
        ui->lcdNumber->display(time);
        show();
        setWindowOpacity(0.6);
    }

}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << event->globalPos();
//    QPoint globalPos = event->globalPos();
//    if(m_Rect.contains(globalPos))
//    {
//        qDebug() << "mouse in rect";
//        setWindowOpacity(0.1);
//        this->hide();
//    }
//    else
//    {
//        qDebug() << "mouse out rect";
//        setWindowOpacity(0.7);
//        this->show();
//    }

}

void MainWidget::createSystemTrayIcon()
{
    m_TrayIcon = new QSystemTrayIcon(this);
    m_TrayIcon->setIcon(QIcon(":/images/system_icon.jpg"));
    m_TrayIcon->setVisible(true);



    createSystemTrayIconContexMenu();

    m_TrayIcon->show();
}

void MainWidget::createSystemTrayIconContexMenu()
{
    m_AboutAction = new QAction("about", this);
    m_TimeShowSettingMenu = new QMenu("Time Setting",this);

    m_HourAction = new QAction("One Hour");
    m_HalfHourAction = new QAction("Half Hour");
    m_FifteenMinutesAction = new QAction("Fifteen Minutes");
    m_TenMinutesAction = new QAction("Ten Minutes");
    m_OneMinutesAction = new QAction("One Minitues");

    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(m_HourAction);
    actionGroup->addAction(m_HalfHourAction);
    actionGroup->addAction(m_FifteenMinutesAction);
    actionGroup->addAction(m_TenMinutesAction);
    actionGroup->addAction(m_OneMinutesAction);
    m_HourAction->setChecked(true);

    m_TimeShowSettingMenu->addAction(m_HourAction);
    m_TimeShowSettingMenu->addAction(m_HalfHourAction);
    m_TimeShowSettingMenu->addAction(m_FifteenMinutesAction);
    m_TimeShowSettingMenu->addAction(m_TenMinutesAction);
    m_TimeShowSettingMenu->addAction(m_OneMinutesAction);


    m_TrayMenu = new QMenu(this);
    m_TrayMenu->addAction(m_AboutAction);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addMenu(m_TimeShowSettingMenu);
    m_TrayIcon->setContextMenu(m_TrayMenu);
}

