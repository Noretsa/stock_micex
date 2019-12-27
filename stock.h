
#include <string>
#ifndef STOCK_H_
#define STOCK_H_

int promtMenuItem();

std::string readJsonHTTP(std::string url);

std::string getStockInfo(std::string stock);

#endif
