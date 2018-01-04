#ifndef RTMINFO_H
#define RTMINFO_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <QString>
#include <QStringList>
#include "json.hpp"

using namespace nlohmann;
using namespace std;

#define NB_STOPS 3

class RtmInfo
{
    QStringList         out_list;
    string              *urls;

public:
    RtmInfo();
    ~RtmInfo();
    /*
     * 0 = Euroméditérranée Gantès
     * 1 = Désirée Clary
     * 2 = Joliette
     */
    QStringList const   &getNextPassage(size_t);
};

#endif // RTMINFO_H
