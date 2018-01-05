#include "rtminfo.h"

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return (size * nmemb);
}

RtmInfo::RtmInfo()
{
    urls = new string[NB_STOPS];
    urls[0] = "http://map.rtm.fr/WebBusServeur/getStationDetails?nomPtReseau=03206&response=application/json&1514987769510";
    urls[1] = "http://map.rtm.fr/WebBusServeur/getStationDetails?nomPtReseau=CLA&response=application/json&1514988035255";
    urls[2] = "http://map.rtm.fr/WebBusServeur/getStationDetails?nomPtReseau=03843&response=application/json&1515080617208";
}


RtmInfo::~RtmInfo()
{
}

QStringList const   &RtmInfo::getNextPassage(size_t stopId)
{
    CURL                *curl;
    string      		readBuffer;
    json                data;

    cout << stopId << endl;
    out_list.clear();
    if (stopId >= NB_STOPS)
        return out_list;
    curl = curl_easy_init();
    if (curl)
      {
        curl_easy_setopt(curl, CURLOPT_URL, urls[stopId].c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        cout << readBuffer << endl;
        if (readBuffer.size() > 0 && readBuffer.find("{") == 0)
        {
            data = nlohmann::json::parse(readBuffer.c_str());
            if (!data["getStationDetailsResponse"]["passage"].is_null())
            {
                if (data["getStationDetailsResponse"]["passage"].is_array())
                {
                    for (auto it = data["getStationDetailsResponse"]["passage"].begin(); it != data["getStationDetailsResponse"]["passage"].end(); ++it)
                    {
                        out_list << QString::fromStdString((*it)["nomLigneCial"].get<string>())
                                << QString::fromStdString(data["getStationDetailsResponse"]["comLieu"].get<string>())
                                << QString::fromStdString((*it)["destination"].get<string>())
                                << QString::fromStdString((*it)["heurePassageReel"].get<string>());
                    }
                }
                else
                    out_list << QString::fromStdString(data["getStationDetailsResponse"]["passage"]["nomLigneCial"].get<string>())
                            << QString::fromStdString(data["getStationDetailsResponse"]["comLieu"].get<string>())
                            << QString::fromStdString(data["getStationDetailsResponse"]["passage"]["destination"].get<string>())
                            << QString::fromStdString(data["getStationDetailsResponse"]["passage"]["heurePassageReel"].get<string>());
            }
        }
    }
    return out_list;
}
