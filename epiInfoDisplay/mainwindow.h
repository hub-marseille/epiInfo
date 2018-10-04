#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QDateTime>
#include <QUrl>
#include <QMainWindow>
#include <QTimer>
#include "rtminfo.h"
#include "intra.h"
#include "infos.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    RtmInfo         rtmInfo;
    Intra           intra;
    Infos           infos;
    QTimer          intraTimer;
    QTimer          rtmTimer;
    QTimer          timeTimer;
    QTimer          infosTimer;

private slots:
    void    updateRtmInfo();
    void    updateTime();
    void    updateInfos();
    void    updateIntra();
};

#endif // MAINWINDOW_H
