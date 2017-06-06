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
    m_TimerID = startTimer(1000);


}



MainWidget::~MainWidget()
{
    killTimer(m_TimerID);
    m_TimerID = -1;
    delete ui;
}

void MainWidget::updateTime()
{

}

void MainWidget::onAboutTriggered(bool btriggered)
{
    if(QSystemTrayIcon::supportsMessages()){
        qDebug() << "Support";
        m_TrayIcon->showMessage("Title", "msg");
    }else{
        qDebug() << "Not Support";
    }
}

void MainWidget::onPlanningTriggered(bool bChecked)
{
    qDebug() << __FILE__;
    QMenu *testMenu = new QMenu();
    QAction *act1 = new QAction("act1", this);
    QAction *act2 = new QAction("act2", this);
    testMenu->addAction(act1);
    testMenu->addAction(act2);
    setContextMenuPolicy(Qt::CustomContextMenu);
    testMenu->exec(mapToGlobal(QPoint(10, 10)));
//    m_PlanningAction->setMenu(testMenu);

}

void MainWidget::onShowRecentPlanningTriggered(bool bTriggered)
{
    qDebug() << __LINE__;
    QMenu *testMenu = new QMenu(this);
    QAction *act1 = new QAction("act1", this);
    QAction *act2 = new QAction("act2", this);
    testMenu->addAction(act1);
    testMenu->addAction(act2);

    testMenu->exec(QPoint(10, 10));
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
        m_TrayIcon->showMessage("Planning", "sleep", QSystemTrayIcon::Information, 5000);
        hide();
    }
    else
    {
        ui->lcdNumber->display(time);
        show();
        setWindowOpacity(0.6);
    }

}


void MainWidget::createSystemTrayIcon()
{
    m_TrayIcon = new QSystemTrayIcon(this);
    m_TrayIcon->setIcon(QIcon(":/images/system_icon.jpg"));
    m_TrayIcon->setVisible(true);// == m_TrayIcon->show();
    // 创建菜单
    createSystemTrayIconContexMenu();
}

void MainWidget::createSystemTrayIconContexMenu()
{
    m_AboutAction = new QAction("about", this);
    connect(m_AboutAction, SIGNAL(triggered(bool)), this, SLOT(onAboutTriggered(bool)));

    m_TimeShowSettingMenu = new QMenu("Time Setting",this);
    m_HourAction = new QAction("One Hour", this);
    m_HourAction->setCheckable(true);
    m_HalfHourAction = new QAction("Half Hour", this);
    m_HalfHourAction->setCheckable(true);
    m_FifteenMinutesAction = new QAction("Fifteen Minutes", this);
    m_FifteenMinutesAction->setCheckable(true);
    m_TenMinutesAction = new QAction("Ten Minutes", this);
    m_TenMinutesAction->setCheckable(true);
    m_OneMinutesAction = new QAction("One Minitues", this);
    m_OneMinutesAction->setCheckable(true);

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

    // 显示主窗口
    m_ShowMainWindow = new QAction(QString::fromLocal8Bit("显示时间窗口(&W)"), this);
    m_ShowMainWindow->setCheckable(true);
    m_ShowMainWindow->setShortcut(Qt::ALT + Qt::Key_W);
    connect(m_ShowMainWindow, SIGNAL(triggered(bool)), this, SLOT(setVisible(bool)));

    // 添加计划
    m_PlanningAction = new QAction(QString::fromLocal8Bit("添加计划任务"), this);
    connect(m_PlanningAction, SIGNAL(triggered(bool)), this, SLOT(onPlanningTriggered(bool)));
    // 显示最近计划
    m_ShowRecentPlan = new QMenu(QString::fromLocal8Bit("显示待完成任务"), this);
    m_TrayMenu = new QMenu(this);
    m_TrayMenu->addAction(m_AboutAction);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addMenu(m_TimeShowSettingMenu);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addAction(m_ShowMainWindow);
    m_TrayMenu->addSeparator();
    m_TrayMenu->addAction(m_PlanningAction);
    m_TrayMenu->addMenu(m_ShowRecentPlan);

    m_TrayIcon->setContextMenu(m_TrayMenu);
}

