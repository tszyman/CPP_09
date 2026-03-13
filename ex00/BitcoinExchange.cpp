/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:26:19 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/13 19:38:20 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>

// 1. Default constructor
BitcoinExchange::BitcoinExchange() {}

// 2. Copy constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {this->_data = src._data;}

// 3. Copy Assignment Operator
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	if (this != &rhs){
		this->_data = rhs._data;
	}
	return *this;
}

// 4. Destructor
BitcoinExchange::~BitcoinExchange() {}

static int isLeapYear(int year){
	return 0;
}

static int getMaxDays(int month, int year){

}



void BitcoinExchange::loadDatabase(const std::string &dbPath) {
	std::ifstream file(dbPath.c_str());
	if(!file.is_open()){
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line); // just to skip the header line

	while(std::getline(file, line)){
		size_t commaPos = line.find(',');
		if (commaPos != std::string::npos){
			std::string date = line.substr(0, commaPos);
			std::string rateStr = line.substr(commaPos + 1);
			float rate = static_cast<float>(std::atof(rateStr.c_str()));	//conversion of rateStr to float
			_data[date] = rate;												//store in db
		}
	}
	file.close();
}

void processInput(const std::string &inputPath){
// 1. getDate: get the date from data
// 2. splitDate: YYYY-MM-DD -> int year, int month, int day
// 3. validate: year: int > 0; month: int 0 < month <= 12; day: 0 < day < 31
// 4. leapYear: check if year is leap: divisable by 4 and if divisable by 100 adn divisable by 400 (2000 = leap, but 1900 not leap)
// 5. dayValidation: if day/month is valid for the year.
}
