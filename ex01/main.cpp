/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:26:35 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:26:40 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./RPN \"expression\"" << std::endl;
		return 1;
	}
	
	try {
		RPN::evaluate(argv[1]);
	} catch (const std::exception &e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}