/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CavalierProjection.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:47:04 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:58:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAVALIERPROJECTION_HPP
# define CAVALIERPROJECTION_HPP

#include "IProjection.hpp"

class CavalierProjection : public IProjection{
	public:
		~CavalierProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif