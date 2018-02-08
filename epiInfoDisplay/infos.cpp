#include "infos.h"

Infos::Infos()
{
    url = "http://epiinfo.livehost.fr/?format=json";
}


Infos::~Infos()
{
}

const string   &Infos::getContent()
{
    CURL                *curl;
    string      		readBuffer;
    json                data;

    cout << "Content" << endl;
    curl = curl_easy_init();
    if (curl)
      {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        cout << readBuffer << endl;
        if (readBuffer.size() > 0 && readBuffer.find("{") == 0)
        {
            data = nlohmann::json::parse(readBuffer.c_str());
            if (!data["content"].is_null())
            {
                content = data["content"].get<string>();
            }
        }
    }
    return content;
}
