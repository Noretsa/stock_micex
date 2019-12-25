

#include <iostream>
#include <fstream>
#include <string>

#include <curl/curl.h>
//#include <json/json.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

// static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
// {
//   size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
//   return written;
// }


int main(int argc, char *argv[]){
    // std::ifstream f("http://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");
    // json obj;
    // f >> obj;
    // std::cout << obj[0]["marketdata"];

    // auto j3 = json::parse("http://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");

    // std::cout << j3.is_object() << '\n';


  CURL *curl_handle;
  static const char *pagefilename = "page.json";
  FILE *pagefile;
  json obj;
//  json *ptr = &obj;

//  ptr = obj;

 


  // if(argc < 2) {
  //   printf("Usage: %s <URL>\n", argv[0]);
  //   return 1;
  // }
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json");
 
  /* Switch on full protocol/debug output while testing */ 
//  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
 
  /* disable progress meter, set to 0L to enable it */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  /* send all data to this function  */ 
//  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  /* open the file */ 
//  pagefile = fopen(pagefilename, "wb");
//  if(pagefile) {
 
    /* write the page body to this file handle */
//      std::cout << "1" << '\n';
//    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, ptr);
      curl_easy_setopt(curl_handle, CURLOPT_READDATA, &obj);

//    std::cout << "2" << '\n';
 
    /* get it! */ 
    curl_easy_perform(curl_handle);


 
    /* close the header file */ 
//    fclose(pagefile);
    //}
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
//  std::ifstream f("page.json");

//  f >> obj;

  std::cout << obj << '\n';
  


    
return 0;
}

