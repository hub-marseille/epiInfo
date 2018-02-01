#ifndef INTRA_H
#define INTRA_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>
#include <fstream>
#include <QApplication>
#include <QDir>
#include "json.hpp"

#define Scifi       "FR/MAR/main/BAT1-SciFi"
#define Cousteau    "FR/MAR/main/BAT1-Cousteau"
#define Guiness     "FR/MAR/main/BAT1-Guiness"
#define CoWorking   "FR/MAR/main/BAT1-CoWorking"
#define Hub         "FR/MAR/main/BAT2-Hub"
#define Retro       "FR/MAR/main/BAT2-Retro"

using namespace std;
using namespace nlohmann;

size_t  write_callback(void *contents, size_t size, size_t nmemb, void *userp);

class   Intra {
public:
    Intra();
    ~Intra();
    bool            getScifi(json);
    bool            getCousteau(json);
    bool            getGuiness(json);
    bool            getRetro(json);
    bool            getHub(json);
    const string    &getUrl() const;
    const string    &getAutologin() const;
    void            connect();
    string          UpdateHour();
private:
    string          url;
    string          autologin;
};

#endif // INTRA_H
