#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

struct latAndLon {
    string latitude;
    string longitude;
};

static size_t WriteCallback(void* contents, size_t size, size_t numMembers, void* userP) {
    ((string*)userP)->append((char*)contents, size * numMembers);
    return size * numMembers;
}

void findLatLon() {
    CURL* locationCurl = curl_easy_init();
    CURLcode code;
    string readLatLon;
    latAndLon location;

    if (locationCurl) {
        curl_easy_setopt(locationCurl, CURLOPT_URL, "https://geocode.maps.co/search?q=Prescott+AZ");

        curl_easy_setopt(locationCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(locationCurl, CURLOPT_WRITEDATA, &readLatLon);
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "graelerg@my.erau.edu");
        code = curl_easy_perform(locationCurl);
        curl_easy_cleanup(locationCurl);

        cout << readLatLon << endl;

        string lat = "\"lat\"";
        string lon = "\"lon\"";
        size_t latLocation = readLatLon.find(lat) + 7;
        size_t lonLocation = readLatLon.find(lon) + 7;

        location.latitude = readLatLon.substr(latLocation, 2);
        location.longitude = readLatLon.substr(lonLocation, 4);

        cout << "Latitude: " << location.latitude << endl;
        cout << "Longitude: " << location.longitude << endl;
    }
}

void forecast() {
    CURL* curl = curl_easy_init();
    CURLcode res;
    string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/gridpoints/TOP/31,80/forecast");
        //curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/points/39.7456,-97.0892");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "graelerg@my.erau.edu");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        cout << readBuffer << endl;
    }
}

int main() {
    //findLatLon();
    forecast();

	return 0;
}