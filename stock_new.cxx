
#include <iostream>
#include <fstream>
#include <string>

#include <curl/curl.h>
//#include <json/json.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

// struct MemoryStruct {
//   int *memory;
//   size_t size;
// };
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(){
    CURL *curl_handle;
    CURLcode res;

    json obj;
    std::string readBuff;
    

  //     struct MemoryStruct chunk;
 
  // chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
  // chunk.size = 0;    /* no data at this point */ 

    
    // curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    if(curl_handle){
	
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");
    
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuff);

    res = curl_easy_perform(curl_handle);
    // if(res != CURLE_OK){
    // 	std::cout << "some" << std::endl;
    // }

    curl_easy_cleanup(curl_handle);
    }

    // free(chunk.memory);
    
    
    // curl_global_cleanup();

    auto j3 = json::parse(readBuff);

    std::cout << j3["marketdata"]["data"][1][24] << '\n';
    std::cout << j3["marketdata"]["data"].is_array() << '\n';
    // int sizeJsonArray = sizeof(j3["marketdata"]["data"][1][0]);
    // std::cout << sizeJsonArray << '\n';
    int i = 0;
    for(auto& el : j3["marketdata"]["columns"].items()){
	std::cout << el.value() << " : " << j3["marketdata"]["data"][1][i] << '\n';
	i++;
    }
    return 0;
}
