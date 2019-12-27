
#include <iostream>
#include <string>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <vector>


#include "nlohmann/json.hpp"
#include "stock.h"

using json = nlohmann::json;

bool pred(const std::pair< std::string, double > &a, const std::pair< std::string, double > &b){
    return a.second > b.second;
}


int main(){

    int variant = promtMenuItem();
    int sumWant = 300000;
    std::vector< std::pair< std::string, double > > vec;

    switch (variant){
    case 1:{
	std::string url_1 = "http://iss.moex.com/iss/statistics/engines/stock/markets/index/analytics/imoex.json?limit=100";
	std::string readBuff_1 = readJsonHTTP(url_1);
	auto obj = json::parse(readBuff_1);
	std::cout << std::left << std::setw(3) << std::setfill(' ') << "#" << "|"
	          << std::left << std::setw(7) << std::setfill(' ') << "Ticker" << "|"
		  // << std::left << std::setw(31) << std::setfill(' ') << "Name" << "|"
		  << std::left << std::setw(7) << std::setfill(' ') << "Weight" << "|"
		  << std::left << std::setw(8) << std::setfill(' ') << "Price" << "|"
		  << std::left << std::setw(8) << std::setfill(' ') << "Change %" << "|"
		  << std::left << std::setw(8) << std::setfill(' ') << "Lot size" << "|"
		  << std::left << std::setw(8) << std::setfill(' ') << "For buy" << "|\n";
	for(auto& el : obj["analytics"]["data"].items()){

	    //создаем пару и запихиваем в нее ticker & weight
	    std::pair< std::string, double > pair;
	    pair.first = std::string(el.value()[2]);
	    pair.second = el.value()[5];

	    //запихиваем в vector pair для того, чтобы отсортировать по индексу, а не по ticker
	    vec.push_back(pair);
	    
	}
	std::sort(vec.begin(), vec.end(), pred);
	int num = 0;
	for(auto p : vec){
	    num++;
	    //сумма текущих акций пропорционально индексу от sumWant
	    int sumIndexRepeat = (p.second / 100) * sumWant;
	    
	    std::string stockInfo = getStockInfo(p.first);
	    auto stock = json::parse(stockInfo);
	    
	    //округленное значение от sumIndexRepeat / Price * Lot size. Необходимое количество для повтора индекса
   	    int forBuyIndex = floor(sumIndexRepeat / (double(stock["marketdata"]["data"][0][37]) * int(stock["securities"]["data"][0][4])));

	    std::cout << std::left << std::setw(3) << std::setfill(' ') << num << "|"
		      << std::left << std::setw(7) << std::setfill(' ') << p.first << "|"
		      // << std::left << std::setw(31) << std::setfill(' ') << std::string(stock["securities"]["data"][0][20]) << "|"
		      << std::left << std::setw(7) << std::setfill(' ') << p.second << "|"
		      << std::left << std::setw(8) << std::setfill(' ') << double(stock["marketdata"]["data"][0][37]) << "|";
	    if(double(stock["marketdata"]["data"][0][25]) < 0.){
		std::cout << "\x1b[31m"<< std::right << std::setw(8) << std::setfill(' ') <<  double(stock["marketdata"]["data"][0][25]) << "\033[0m" << "|";
	    }else if(double(stock["marketdata"]["data"][0][25]) > 0.){
		std::cout << "\x1b[32m"<< std::right << std::setw(8) << std::setfill(' ') <<  double(stock["marketdata"]["data"][0][25]) << "\033[0m" << "|";
	    }else {
		std::cout << "\x1b[37m"<< std::right << std::setw(8) << std::setfill(' ') <<  double(stock["marketdata"]["data"][0][25]) << "\033[0m" << "|";
	    }
	    std::cout << std::left << std::setw(8) << std::setfill(' ') << int(stock["securities"]["data"][0][4]) << "|"
		      << std::left << std::setw(8) << std::setfill(' ') << forBuyIndex * int(stock["securities"]["data"][0][4]) << "|" << std::endl;
	}
	// std::cout << "\x1b[31mTexting\033[0m\t\t";
	break;
    }
    case 2:{
	std::string url_2 = "http://iss.moex.com/iss/engines/stock/markets/shares/securities/moex.json";
	std::string readBuff_2 = readJsonHTTP(url_2);
	auto j3 = json::parse(readBuff_2);
	int i = 0;
	for(auto& el : j3["marketdata"]["columns"].items()){
	    std::cout << el.value() << " : " << j3["marketdata"]["data"][1][i] << '\n';
	    i++;
	}
	break;
    }
    case 3:{
	std::cout << "Exit from programs. Buy.\n";
	exit(EXIT_SUCCESS);
	break;
    }
    default:{
	std::cerr << "You are choose wrong variant!" << std::endl;
	exit(EXIT_FAILURE);
    }
    }

    return 0;
}
