/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:26:23 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:26:29 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv){
	// 1. Check for correct number of arguments

	if (argc != 2) {
		std::cerr << "Error: no input file given." << std::endl;
		return 1;
	}

	BitcoinExchange btc;

	// 2. Load the internal database (data.csv)
	// It's a good idea to have this return a bool or handle errors internally.
	btc.loadDatabase("data.csv");

	// 3. Process the user's input file provided as an argument
	btc.processInput(argv[1]);

	return 0;
}
