#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLCDNumber>
#include <QTimer>
#include <QSystemTrayIcon>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();



public slots:
//    void mouseMoveEvent();
    void updateTime();
    void onAboutTriggered(bool btriggered);
    void onPlanningTriggered(bool bChecked);
    void onShowRecentPlanningTriggered(bool bTriggered);

private:
    void setWidgetSizeAndPos();
    QRect getDesktopSize();
    bool isInRect(QPoint &point);

    void timerEvent(QTimerEvent* event);

    void createSystemTrayIcon();
    void createSystemTrayIconContexMenu();


private:
    Ui::MainWidget *ui;
    QLCDNumber *m_LCDNumber;
    QSystemTrayIcon *m_TrayIcon;

    QMenu   *m_TrayMenu;
    QAction *m_AboutAction; //����

    QMenu   *m_TimeShowSettingMenu; // ʱ������
    QAction *m_HalfHourAction;
    QAction *m_HourAction;
    QAction *m_FifteenMinutesAction;
    QAction *m_TenMinutesAction;
    QAction *m_OneMinutesAction;

    QAction *m_ShowMainWindow; // ��ʾʱ�䴰��
    QMenu   *m_ShowRecentPlan;
    QAction *m_PlanningAction; // ��Ӽƻ��¼�


    QRect m_Rect;
    static const int m_Width = 500;
    static const int m_Height = 100;
    static const int m_Spacer = 50;

    int m_TimerID;

};

#endif // MAINWIDGET_H
