/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:27:21 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:27:22 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

class PmergeMe {
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& src);
		PmergeMe& operator=(const PmergeMe& rhs);
		~PmergeMe();

		// Sorting entry points
		void sortVector(int ac, char **av);
		void sortDeque(int ac, char **av);

	private:
		// Core Ford-Johnson logic (two versions because different container specific iterators)
		void fordJohnsonVector(std::vector<int>& containter);
		void fordJohnsonDeque(std::deque<int>& containter);

		// Helper for printing resutls
		void printSeqV(const std::string& prefix, const std::vector<int>& v);
		void printSeqD(const std::string& prefix, const std::deque<int>& d);
};

#endif
