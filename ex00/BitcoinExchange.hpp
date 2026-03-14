/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:26:13 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/13 18:32:05 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::map<std::string, float> _data;  // Database container
		// helper functions
		bool isLeapYear(int year) const;
		bool isValidDate(const std::string& date) const;


	public:
		// OCF
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);
		~BitcoinExchange();

		// Core logic
		void loadDatabase(const std::string &dbPath);
		void processInput(const std::string &inputPath);
};

#endif
