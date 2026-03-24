/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:27:05 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:27:11 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv){
	// Check args
	if (argc < 2){
		std::cout << "Error: No input provided. Usage: /PmergeMe [positive integers...]" << std::endl;
		return 1;
	}
	PmergeMe sorter;

	try{
		sorter.sortVector(argc, argv);
		sorter.sortDeque(argc, argv);

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
