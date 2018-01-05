#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateRtmInfo();
    rtmTimer.start(30000);
    connect(&rtmTimer, SIGNAL(timeout()), this, SLOT(updateRtmInfo()));
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::updateRtmInfo()
{
    QStringList passages;
    QString     to_write;

    cout << "Updating RTM" << std::endl;
    passages = rtmInfo.getNextPassage(2);
    for (int i = 0; i < passages.size(); i += 4)
    {
        to_write += passages.at(i) + " (" + passages.at(i + 1)+ ") vers " + passages.at(i + 2) + ": passage à " + passages.at(i + 3) + "\n";
    }
    ui->bus->setText(to_write);
    to_write.clear();
    passages = rtmInfo.getNextPassage(1);
    for (int i = 0; i < passages.size(); i += 4)
    {
        to_write += passages.at(i) + " (" + passages.at(i + 1)+ ") vers " + passages.at(i + 2) + ": passage à " + passages.at(i + 3) + "\n";
    }
    ui->metro->setText(to_write);
    to_write.clear();
    passages = rtmInfo.getNextPassage(0);
    for (int i = 0; i < passages.size(); i += 4)
    {
        to_write += passages.at(i) +  " (" + passages.at(i + 1) + ") vers " + passages.at(i + 2) + ": passage à " + passages.at(i + 3) + "\n";
    }
    ui->tram->setText(to_write);
}
