#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->setStyleSheet("background-image:url(\"/background.png\"); background-position: center;");
    updateInfos();
    updateRtmInfo();
    updateTime();
    updateIntra();
    infosTimer.start(60000);
    connect(&infosTimer, SIGNAL(timeout()), this, SLOT(updateInfos()));
    rtmTimer.start(30000);
    connect(&rtmTimer, SIGNAL(timeout()), this, SLOT(updateRtmInfo()));
    intraTimer.start(60000);
    connect(&rtmTimer, SIGNAL(timeout()), this, SLOT(updateIntra()));
    timeTimer.start(1000);
    connect(&timeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));

    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void    MainWindow::updateInfos()
{
    string  content = infos.getContent().c_str();

    cout << "UpdateInfos" << endl;
    if (content.empty())
        ui->information->setText("Aucune information disponible");
    else
        ui->information->setText(infos.getContent().c_str());
}

void    MainWindow::updateIntra()
{
    CURL    *curl;
    string      		readBuffer;
    json                data;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "");
        curl_easy_setopt(curl, CURLOPT_URL, intra.getAutologin().c_str());
        curl_easy_perform(curl);
        curl_easy_setopt(curl, CURLOPT_URL, intra.getUrl().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        if (readBuffer.size() > 0&& readBuffer.find("[") == 0)
        {
            data = nlohmann::json::parse(readBuffer.c_str());
            if (intra.getScifi(data) == true) {
                ui->sci_room->setStyleSheet("QLabel { background-color : rgb(231, 76, 60);}");
            } else {
                ui->sci_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            }
            if (intra.getCousteau(data) == true) {
                ui->cou_room->setStyleSheet("QLabel { background-color : rgb(231, 76, 60);}");
            } else {
                ui->cou_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            }
            if (intra.getGuiness(data) == true) {
                ui->gui_room->setStyleSheet("QLabel { background-color : rgb(231, 76, 60);}");
            } else {
                ui->gui_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            }
            if (intra.getHub(data) == true) {
                ui->hub_room->setStyleSheet("QLabel { background-color : rgb(231, 76, 60);}");
            } else {
                ui->hub_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            }
            if (intra.getRetro(data) == true) {
                ui->retro_room->setStyleSheet("QLabel { background-color : rgb(231, 76, 60);}");
            } else {
                ui->retro_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            }
        } else {
            ui->sci_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            ui->gui_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            ui->cou_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            ui->retro_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
            ui->hub_room->setStyleSheet("QLabel { background-color : rgb(46, 204, 113);}");
        }
        curl_easy_cleanup(curl);
    }
}

void    MainWindow::updateRtmInfo()
{
    QStringList passages;
    QString     to_write;
    QString     hours;

    cout << "Updating RTM" << std::endl;
    passages = rtmInfo.getNextPassage(2);
    if (passages.isEmpty()) {
        to_write = "Aucune informations\n";
        ui->bus_error->setText(to_write);
        ui->bus->setText("");
        ui->bus_hour->setText("");
    } else {
        for (int i = 0; i < passages.size(); i += 4)
        {
            to_write += passages.at(i) + "\t ➔ \t" + passages.at(i + 2) + "\n";
            hours += passages.at(i + 3) + "\n";
        }
        ui->bus->setText(to_write);
        ui->bus_hour->setText(hours);
        ui->bus_error->setText("");
    }
    hours.clear();
    to_write.clear();
    passages = rtmInfo.getNextPassage(1);
    if (passages.isEmpty()) {
        to_write = "Aucune informations\n";
        ui->metro_error->setText(to_write);
        ui->metro->setText("");
        ui->metro_hour->setText("");
    } else {
        for (int i = 0; i < passages.size(); i += 4)
        {
            to_write += passages.at(i) + "\t ➔ \t" + passages.at(i + 2) + "\n";
            hours += passages.at(i + 3) + "\n";
            ui->metro->setText(to_write);
            ui->metro_hour->setText(hours);
            ui->metro_error->setText("");
        }
    }
    hours.clear();
    to_write.clear();
    passages = rtmInfo.getNextPassage(0);
    if (passages.isEmpty()) {
        to_write = "Aucune informations\n";
        ui->tram_error->setText(to_write);
        ui->tram->setText("");
        ui->tram_hour->setText("");
    } else {
        for (int i = 0; i < passages.size(); i += 4)
        {
            to_write += passages.at(i) + "\t ➔ \t" + passages.at(i + 2) + "\n";
            hours += passages.at(i + 3) + "\n";
        }
        ui->tram->setText(to_write);
        ui->tram_hour->setText(hours);
        ui->tram_error->setText("");
    }
}

void    MainWindow::updateTime()
{
    ui->time->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
}
