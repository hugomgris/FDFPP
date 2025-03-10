/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsometricProjection.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:46:01 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:15:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/IsometricProjection.hpp"

IsometricProjection::~IsometricProjection(){}

std::pair<int, int> IsometricProjection::project(int &x, int &y, int &z) const{
		int newX = (x - y) * std::cos(M_PI / 6);
		int newY = (x + y) * std::sin(M_PI / 6) - z;
		return {newX, newY};
}
