#include "intra.h"
#include <ctime>

Intra::Intra()
{
    time_t      now = time(0);
    struct tm   tstruct = *localtime(&now);
    char        buf[80];
    string      current;
    QFile       file(":/login.txt");

    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    current = strdup(buf);
    url = "https://intra.epitech.eu/planning/load?format=json&start=" + current + "&end=" + current;
    if (file.open(QFile::ReadOnly)) {
        QString content = file.readLine();
        content.remove(QChar('\n'), Qt::CaseInsensitive);
        autologin = content.toStdString();
        cout << "\"" << autologin << "\"" << endl;
    }
}

Intra::~Intra()
{
}

string  Intra::UpdateHour()
{
    time_t      now = time(0);
    struct tm   tstruct = *localtime(&now);
    char        buf[20];
    string      hour;

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    hour = strdup(buf);
    return hour;
}

const string  &Intra::getUrl() const
{
    return (url);
}

const string    &Intra::getAutologin() const
{
    return (autologin);
}

bool    Intra::getScifi(json data)
{
    cout << "Scifi" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (!(*it).is_null()) {
            if (!(*it)["room"]["code"].is_null() && !(*it)["start"].is_null() && !(*it)["end"].is_null()) {
                if ((*it)["room"]["code"].get<string>().compare(Scifi) == 0 && UpdateHour() >= (*it)["start"].get<string>() && UpdateHour() <= (*it)["end"].get<string>()) {
                    cout << (*it)["room"]["code"].get<string>() << " / " << (*it)["start"].get<string>() << " à " << (*it)["end"].get<string>() << endl;
                    return (true);
                }
            }
        }
    }
    return (false);
}

bool    Intra::getCousteau(json data)
{
    cout << "Cousteau" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (!(*it).is_null()) {
            if (!(*it)["room"]["code"].is_null() && !(*it)["start"].is_null() && !(*it)["end"].is_null()) {
                if ((*it)["room"]["code"].get<string>().compare(Cousteau) == 0 && UpdateHour() >= (*it)["start"].get<string>() && UpdateHour() <= (*it)["end"].get<string>()) {
                    cout << (*it)["room"]["code"].get<string>() << " / " << (*it)["start"].get<string>() << " à " << (*it)["end"].get<string>() << endl;
                    return (true);
                }
            }
        }
    }
    return (false);
}

bool    Intra::getGuiness(json data)
{
    cout << "Guiness" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (!(*it).is_null()) {
            if (!(*it)["room"]["code"].is_null() && !(*it)["start"].is_null() && !(*it)["end"].is_null()) {
                if ((*it)["room"]["code"].get<string>().compare(Guiness) == 0 && UpdateHour() >= (*it)["start"].get<string>() && UpdateHour() <= (*it)["end"].get<string>()) {
                    cout << (*it)["room"]["code"].get<string>() << " / " << (*it)["start"].get<string>() << " à " << (*it)["end"].get<string>() << endl;
                    return (true);
                }
            }
        }
    }
    return (false);
}

bool    Intra::getHub(json data)
{
    cout << "Hub" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (!(*it).is_null()) {
            if (!(*it)["room"]["code"].is_null() && !(*it)["start"].is_null() && !(*it)["end"].is_null()) {
                if ((*it)["room"]["code"].get<string>().compare(Hub) == 0 && UpdateHour() >= (*it)["start"].get<string>() && UpdateHour() <= (*it)["end"].get<string>()) {
                    cout << (*it)["room"]["code"].get<string>() << " / " << (*it)["start"].get<string>() << " à " << (*it)["end"].get<string>() << endl;
                    return (true);
                }
            }
        }
    }
    return (false);
}

bool    Intra::getRetro(json data)
{
    cout << "Retro" << endl;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (!(*it).is_null()) {
            if (!(*it)["room"]["code"].is_null() && !(*it)["start"].is_null() && !(*it)["end"].is_null()) {
                if ((*it)["room"]["code"].get<string>().compare(Retro) == 0 && UpdateHour() >= (*it)["start"].get<string>() && UpdateHour() <= (*it)["end"].get<string>()) {
                    cout << (*it)["room"]["code"].get<string>() << " / " << (*it)["start"].get<string>() << " à " << (*it)["end"].get<string>() << endl;
                    return (true);
                }
            }
        }
    }
    return (false);
}
