/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:27:00 by tszymans          #+#    #+#             */
/*   Updated: 2026/03/12 20:27:01 by tszymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

class RPN {
	public:
		RPN();
		RPN(const RPN& src);
		RPN& operator=(const RPN& rhs);
		~RPN();

		static void evaluate(std::string expr);
};

#endif
