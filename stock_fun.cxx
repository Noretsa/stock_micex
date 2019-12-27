
#include <string>
#include <iostream>

#include <curl/curl.h>
#include "stock.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string *)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int promtMenuItem(){
    int variant;
    std::cout << "Choose what you want to do: \n" << std::endl;

    std::cout << "1. Look at MICEX index balance\n"
	      << "2. Look at my stocks\n"
	      << "3. Exit\n" << std::endl;
    std::cout << ">>> ";
    std::cin >> variant;
    std::cin.get();
    return variant;
}

std::string readJsonHTTP(std::string url){
    CURL *curl_handle;
    CURLcode res;
    std::string readBuff;

    curl_handle = curl_easy_init();
    if(curl_handle){
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuff);

	res = curl_easy_perform(curl_handle);

	curl_easy_cleanup(curl_handle);
    }

    return readBuff;
}

std::string getStockInfo(std::string stock){
    std::string url = "https://iss.moex.com/iss/engines/stock/markets/shares/boardgroups/57/securities/" + stock + ".json";
    // std::cout << url << std::endl;
    CURL *curl_handle;
    CURLcode res;
    std::string readBuff;

    curl_handle = curl_easy_init();
    if(curl_handle){
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuff);

	res = curl_easy_perform(curl_handle);

	curl_easy_cleanup(curl_handle);
    }

    return readBuff;

}
