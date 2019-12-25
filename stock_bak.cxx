

#include <iostream>
#include <string>

#include <curl/curl.h>
//#include <json/json.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;



int main(){
//    std::string url("https://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");
    CURL* curl = curl_easy_init();
    CURLcode res;

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, "https://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");

// Don't bother trying IPv6, which would increase DNS resolution time.
curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

// Don't wait forever, time out after 10 seconds.
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

// Follow HTTP redirects if necessary.
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

//curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, 1);

//std::istringstream httpData;
//std::unique_ptr<std::string> httpData(new std::string());

//curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

json obj;
curl >> obj;
//obj = res = curl_easy_perform(curl);
//obj = curl_easy_perform(curl);
// if(res != CURLE_OK){
//     std::cout << "some\n";
// }
curl_easy_cleanup(curl);
//std::cout << obj.is_null() << '\n';
for (json::iterator it = obj.begin(); it != obj.end(); ++it) {
  std::cout << it.key() << " : " << it.value() << "\n";
}
// for(json::iterator it = obj.begin(); it !=obj.end(); ++it){
//     std::cout << *it << '\n';
// }
//httpData >> obj;

// // Response information.
// int httpCode(0);
// std::unique_ptr<std::string> httpData(new std::string());
// //std::stringstream httpData;

// // Hook up data handling function.
// curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

// // Hook up data container (will be passed as the last parameter to the
// // callback handling function).  Can be any pointer type, since it will
// // internally be passed as a void pointer.

// // Run our HTTP GET command, capture the HTTP response code, and clean up.
// curl_easy_perform(curl);
// curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
// curl_easy_cleanup(curl);

// if (httpCode == 200){

    
//     std::cout << "\nGot successful response from " << url << std::endl;
//     // Json::CharReaderBuilder charBuilder;
//     // std::string errs;
//     // if(Json::parseFromStream(charBuilder, httpData, &jsonData, &errs)){
//     // 	std::cout << "Successfully parsed JSON data" << std::endl;
//     // 	std::cout << "\nJSON data received:" << std::endl;
//     // 	std::cout << jsonData.toStyledString() << std::endl;

// // const std::string dateString(jsonData["date"].asString());
// // const std::size_t unixTimeMs(
// // jsonData["milliseconds_since_epoch"].asUInt64());
// // const std::string timeString(jsonData["time"].asString());
// 	// std::string marketString(jsonData["marketdata"].asString());

// 	// std::cout << "Natively parsed:" << std::endl;
// 	// std::cout << "\tDate string: " << marketString << std::endl;
// 	// // std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
// 	// // std::cout << "\tTime string: " << timeString << std::endl;
// 	// std::cout << std::endl;

// }
	

    
return 0;
}

