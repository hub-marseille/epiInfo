#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QMainWindow>
#include <QTimer>
#include "rtminfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    RtmInfo         rtmInfo;
    QTimer          rtmTimer;
    QTimer          timeTimer;

private slots:
    void    updateRtmInfo();
    void    updateTime();
};

#endif // MAINWINDOW_H
