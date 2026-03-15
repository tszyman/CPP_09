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
#include <cstdlib>

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

bool BitcoinExchange::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	// Check if the date is properly formatted
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	
	// Check if all chars are digits
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i])) 
			return false;
	}

	/* More general approach to splitting but probably not required since dates are YYYY-MM-DD and we assume that year > 999
		size_t firstHyphen = date.find('-');
		size_t secondHyphen = date.find('-', firstHyphen + 1);

		// We extract substrings and convert to int using atoi
		int year = std::atoi(date.substr(0, firstHyphen).c_str());
		int month = std::atoi(date.substr(firstHyphen + 1, secondHyphen - firstHyphen - 1).c_str());
		int day = std::atoi(date.substr(secondHyphen + 1).c_str());
	*/
	
	// Split and convert using atoi
	int year = std::atoi(date.substr(0,4).c_str()); // extract year
	int month = std::atoi(date.substr(5,2).c_str()); // extract month
	int day = std::atoi(date.substr(8,2).c_str()); // extract day

	// Validation of individual values
	if (year < 2009 || month < 1 || month > 12 || day < 0 || day > 31) // Bitcoin started in 2009, no need to check before
		return false;
	
	// Calculation of days in specific month:
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year))
		daysInMonth[1] = 29;

	return (day <= daysInMonth[month - 1]);
}

void BitcoinExchange::calculateValue(const std::string& date, float value) {
	std::map<std::string, float>::iterator it = _data.lower_bound(date);

	// If exact date not found, lower_bound returns the first element GREATER than date
	if (it == _data.end() || it->first != date) {
		if (it == _data.begin()) {
			std::cerr << "Error: date predates database => " << date << std::endl;
			return;
		}
		--it; // Move back to the nearest lower date
	}
	float result = value * it->second;
	std::cout << date << " => " << value << " = " << result << std::endl;
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
	// TESTS
	std::cout << "Database loaded with " << _data.size() << " entries." << std::endl;

	file.close();
}

void BitcoinExchange::processInput(const std::string &inputPath){
	// Loading input file
	std::ifstream file(inputPath.c_str());
	if(!file.is_open()) {
		std::cerr << "Error: could not open input file." << std::endl;
	}
	std::string line;
	std::getline(file, line);

	while(std::getline(file, line)){
		if (line.empty()) continue;
		
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos){
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipePos - 1);
		std::string valueStr = line.substr(pipePos + 1);
		
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		/* Check if needed, not sure if required
			char* endptr;
			float value = std::strtof(valueStr.c_str(), &endptr);
		*/
		float value = static_cast<float>(std::atof(valueStr.c_str()));
		// Range check: 0 < value < 1000
		if (value < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
		} else if (value > 1000) {
			std::cerr << "Error: too large a number." << std::endl;
		} else {
			this->calculateValue(date, value);
		}

		// TESTS 
		// std::cout << "Valid date: " << date << std::endl;
		// std::cout << "Valid value: " << value << std::endl;


	}
}
