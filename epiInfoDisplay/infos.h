#ifndef INFOS_H
#define INFOS_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>
#include <fstream>
#include <QApplication>
#include <QFile>
#include "json.hpp"

using namespace std;
using namespace nlohmann;

size_t  write_callback(void *contents, size_t size, size_t nmemb, void *userp);

class   Infos {
public:
    Infos();
    ~Infos();
    const string    &getContent();
private:
    string          content;
    string          url;
};


#endif // INFOS_H
