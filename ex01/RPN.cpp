/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:26:52 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/26 17:29:00 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>

void RPN::evaluate(std::string expr){
	std::stack<int> s;

	for(size_t i = 0; i < expr.length(); ++i){
		char c = expr[i];
		if (isspace(c))
			continue;
		if (isdigit(c)){
			s.push(c - '0');
		} else if (c == '+' || c == '-' || c == '*' || c == '/') {
			// Checking if at least 2 operands on the stack to perform operation
			if (s.size() < 2) {
				std::cerr << "Error: not enough operands on the stack" << std:: endl;
				return;
			}
			int b = s.top(); s.pop(); // taking rhs operand from the stack
			int a = s.top(); s.pop(); // taking lhs operand from the stack

			// operations
			if (c == '+')
				s.push(a + b);
			if (c == '-')
				s.push(a - b);
			if (c == '*')
				s.push( a * b);
			if (c == '/') {
				if (b == 0){
					std::cerr << "Error: Division by zero" << std::endl;
					return;
				}
				s.push(a / b);
			}
		} else {
			std::cerr << "Error: (other)" << std::endl;
			return;
		}
	}
	if (s.size() != 1){
		std::cerr << "Error: incorrect number of operands" << std::endl;
		return;
	}
	std::cout << s.top() << std::endl;
}
