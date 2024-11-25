#ifndef WMS_LOAD_H
#define WMS_LOAD_H

#include <iostream>
#include <curl/curl.h>
#include <fstream>

class WMSLoader {
public:
    WMSLoader(const std::string& url, const std::string& output_file);
    ~WMSLoader();

    bool performRequest();

private:
    std::string wms_url;
    std::string output_file;

    static size_t writeCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
};

#endif // WMS_LOAD_H

