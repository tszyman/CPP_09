/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:27:16 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:27:17 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iterator>

//Constructor
PmergeMe::PmergeMe() {}
//Copy constructor
PmergeMe::PmergeMe(const PmergeMe& src) {*this = src;}
//Copy Assignment Operator
PmergeMe &PmergeMe::operator=(const PmergeMe& rhs) {
	if (this != &rhs){
		//If memeber variables added to class, should be copied here: 
		//this->_myVector = src._myVector
	}
	return *this;
}
//Destructor
PmergeMe::~PmergeMe(){} //Clean up resources. Since STL containers handle their own memory, this remains empty unless use 'new'

void PmergeMe::printSeqV(const std::string& prefix, const std::vector<int>& v){
	std::cout << prefix;
	if (v.size() <= 10){
		for (size_t i = 0; i < v.size(); ++i){
			std::cout << v[i] << (i == v.size() - 1 ? "" : " ");
		}
	}
	else {
		// Print first 5 elements
		for (int i = 0; i < 5; ++i){
			std::cout << v[i] << " ";
		}
		std::cout << "[...] ";
		// Print last 5 elements
		for (size_t i = v.size() - 5; i < v.size(); ++i){
			std::cout << v[i] << (i == v.size() - 1 ? "" : " ");
		}
	}
	std::cout << std::endl;
}

void PmergeMe::printSeqD(const std::string& prefix, const std::deque<int>& d){
	std::cout << prefix;
	// deque needs an iterator to iterate through elements
	std::deque<int>::const_iterator it;
	if (d.size() <= 10){
		for (it = d.begin(); it != d.end(); ++it){
			std::cout << *it << (it + 1 == d.end() ? "" : " ");
		}
	}
	else {
		it = d.begin();
		for (int i = 0; i < 5; ++i, ++it){
			std::cout << *it << " ";
		}
		std::cout << "[...] ";
		it = d.end() - 5;
		for (;it != d.end(); ++it){
			std::cout << *it << (it + 1 == d.end() ? "" : " ");
		}
	}
	std::cout << std::endl;
}

/**
 *  The Jacobsthal sequence (1, 3, 5, 11, 21...) defines the optimal insertion order
 * to minimize comparisons in the worst-case scenario.
 */

static std::vector<int> genJacobV(int n){
	std::vector<int> jacob;
	jacob.push_back(1);
	if (n < 3) return jacob;
	jacob.push_back(3);
	while (jacob.back() < n){
		int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return jacob;
}

static std::deque<int> genJacobD(int n){
	std::deque<int> jacob;
	jacob.push_back(1);
	if (n < 3) return jacob;
	jacob.push_back(3);
	while (jacob.back() < n){
		int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return jacob;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& container){
	int n = container.size();
	if (n <= 1)
		return;
	
	// 1. Pairing
	std::vector<std::pair<int, int> > pairs;
	int leftover = -1;
	bool hasLeftover = false;

	for (size_t i = 0; i < container.size() - 1; i += 2){
		int first = container[i];
		int second = container[i+1];
		if (first < second) std::swap(first, second); // putting bigger number as first, smaller as second
		pairs.push_back(std::make_pair(first, second));
	}
		// check if leftovers
	if (n % 2 != 0){
		leftover = container.back();
		hasLeftover = true;
	}
	// 2. Recursive Sort of Winners
	std::vector<int> mainChain;
	for(size_t i = 0; i < pairs.size(); ++i){
		mainChain.push_back(pairs[i].first);
	}
		//recursively following
	fordJohnsonVector(mainChain);

	// 3. Setup Pend and initial Main Chain
	std::vector<int> pend;
	for(size_t i = 0; i < pairs.size(); ++i){
		pend.push_back(pairs[i].second);
	}
		//The first element of pend is 100% sure smaller than the first element of the sorted mainChain, so we insert it at the front with no comparisons
	if (!pend.empty()){
		mainChain.insert(mainChain.begin(), pend[0]);
	}

	// 4. Binary Insertion using Jacobsthal order
	std::vector<int> jacob = genJacobV(pend.size());
	std::vector<bool> inserted(pend.size(), false);
	inserted[0] = true;
	for (size_t i = 0; i < jacob.size(); ++i){
		int targetIdx = std::min(jacob[i], (int)pend.size() - 1);
		//insert in reverse order from the Jacobsthal index down to the previous one
		for (int j = targetIdx; j > 0 && !inserted[j]; --j){
			std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
			mainChain.insert(it, pend[j]);
			inserted[j] = true;
		}
	}

	// 5. Final leftover insertion (if odd elements)
	if (hasLeftover){
		std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
		mainChain.insert(it, leftover);
	}
	container = mainChain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& container){
	int n = container.size();
	if (n <= 1)
		return;
	
	// 1. Pairing
	std::deque<std::pair<int, int> > pairs;
	int leftover = -1;
	bool hasLeftover = false;
	for (size_t i = 0; i < container.size() - 1; i += 2){
		int first = container[i];
		int second = container[i + 1];
		if (first < second) std::swap(first, second);
		pairs.push_back(std::make_pair(first, second));
	}
	if (n % 2 != 0){
		leftover = container.back();
		hasLeftover = true;
	}
	// 2. Recursive Sort of Winners
	std::deque<int> mainChain;
	for(size_t i = 0; i < pairs.size(); ++i){
		mainChain.push_back(pairs[i].first);
	}
	fordJohnsonDeque(mainChain);
	// 3. Setup Pend and initial Main Chain
	std::deque<int> pend;
	for (size_t i = 0; i < pairs.size(); ++i){
		pend.push_back(pairs[i].second);
	}
	//The first element of pend is 100% sure smaller than the first element of the sorted mainChain, so we insert it at the front with no comparisons
	if (!pend.empty()){
		mainChain.push_front(pend[0]);
	}
	// 4. Binary Insertion using Jacobsthal order
	std::deque<int> jacob = genJacobD(pend.size());
	std::deque<bool> inserted(pend.size(), false);
	inserted[0] = true;
	for (size_t i = 1; i < jacob.size(); ++i){
		int targetIdx = std::min(jacob[i], (int)pend.size() - 1);
		for (int j = targetIdx; j > 0 && !inserted[j]; --j){		// why &&!inserted[j], and in jacobGenV not?
			std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
			mainChain.insert(it, pend[j]);
			inserted[j] = true;
		}
	}
	// 5. Final leftover insertion
	if(hasLeftover){
		std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
		mainChain.insert(it, leftover);
	}
	container = mainChain;
}

void PmergeMe::sortVector(int ac, char **av){
	std::vector<int> vec;
	std::cout << "--- Sorting with Vector ---" << std::endl;
	for (int i = 1; i < ac; ++i){
		int val = std::atoi(av[i]);
		if (val < 0)
			throw std::runtime_error("Error: negative number");
		vec.push_back(val);
	}
	printSeqV("Before: ", vec);

	clock_t start = clock();
	fordJohnsonVector(vec);
	clock_t end = clock();

	printSeqV("After: ", vec);
	double time = static_cast<double>(end-start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process: " << vec.size() << " elements with std::vector: " << time << " us" << std::endl;

}

void PmergeMe::sortDeque(int ac, char **av){
	std::deque<int> deq;
	std::cout << "--- Sorting with Deque ---" << std::endl;
	for (int i = 1; i < ac; ++i){
		int val = std::atoi(av[i]);
		if (val < 0)
			throw std::runtime_error("Error: negative number");
		deq.push_back(val);
	}
	printSeqD("Before: ", deq);

	clock_t start = clock();
	fordJohnsonDeque(deq);
	clock_t end = clock();

	printSeqD("After: ", deq);
	double time = static_cast<double>(end-start) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process: " << deq.size() << " elements with std::deque: " << time << " us" << std::endl;
}