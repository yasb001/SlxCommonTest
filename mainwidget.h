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

private:
    void setWidgetSizeAndPos();
    QRect getDesktopSize();
    bool isInRect(QPoint &point);

    void timerEvent(QTimerEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void createSystemTrayIcon();
    void createSystemTrayIconContexMenu();


private:
    Ui::MainWidget *ui;
    QLCDNumber *m_LCDNumber;
    QSystemTrayIcon *m_TrayIcon;

    QMenu   *m_TrayMenu;
    QAction *m_AboutAction; // 关于

    QMenu *m_TimeShowSettingMenu; // 时间设置
    QAction *m_HalfHourAction;
    QAction *m_HourAction;
    QAction *m_FifteenMinutesAction;
    QAction *m_TenMinutesAction;
    QAction *m_OneMinutesAction;

    QAction *m_SheduleAction; // 计划设置


    QRect m_Rect;
    static const int m_Width = 500;
    static const int m_Height = 100;
    static const int m_Spacer = 50;

};

#endif // MAINWIDGET_H
