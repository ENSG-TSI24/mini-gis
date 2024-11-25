#include "WMS_Load.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

WMSLoader::WMSLoader(const std::string& url, const std::string& output_file)
    : wms_url(url), output_file(output_file) {}

WMSLoader::~WMSLoader() {}

size_t WMSLoader::writeCallback(void* ptr, size_t size, size_t nmemb, void* userdata) {
    std::ofstream* out = static_cast<std::ofstream*>(userdata);
    out->write(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

bool WMSLoader::performRequest() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur d'initialisation de libcurl !" << std::endl;
        return false;
    }

    std::ofstream file(output_file, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie !" << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, wms_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Erreur dans la requête WMS : " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
    file.close();

    return res == CURLE_OK;
}
