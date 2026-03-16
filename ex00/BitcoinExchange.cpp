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
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
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

float BitcoinExchange::validateValue(const std::string& valueStr) const {
	/** 
	 * Returns the float value if valid.
	 * Returns -1.0 if not a positive number.
	 * Returns -2.0 if too large.
	 * Returns -3.0 for "bad input" (garbage, etc.)
	 * Returns -4.0 for "bad input" (when empty)
	 */
	// 1. Check for empty string or only whiltespace
	if (valueStr.empty() || valueStr.find_first_not_of(" \t\r\n") == std::string::npos){
		//std::cerr << "Error: bad input => " << line << std::endl;
		return -4.0f; // bad input
	}
	char* endptr;
	double val_tmp = std::strtod(valueStr.c_str(), &endptr);
	// we need to check what follows the value, if spaces - need to go to the end
	while (std::isspace(*endptr))
		endptr++;
	if (*endptr != '\0')
		return -3.0f;
	
	if (val_tmp < 0)
		return -1.0f;
	if (val_tmp > 1000)
		return -2.0f;

	return static_cast<float>(val_tmp);
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

		// date validation
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// value validation
		float value = validateValue(valueStr);

		if (value == -1.0f) {
			std::cerr << "Error: not a positive number." << std::endl;
		} else if (value == -2.0) {
			std::cerr << "Error: too large a number." << std::endl;
		} else if (value == -3.0f) {
			std::cerr << "Error: bad input => " << valueStr << std::endl;
		} else if (value == -4.0f) {
			std::cerr << "Error: bad input => " << line << std::endl;
		} else {
			// final calculations
			this->calculateValue(date, value);
		}
	}
}
