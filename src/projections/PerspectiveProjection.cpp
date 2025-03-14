/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerspectiveProjection.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:05 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/PerspectiveProjection.hpp"

PerspectiveProjection::PerspectiveProjection(double distance) : _distance(distance) {}

PerspectiveProjection::~PerspectiveProjection(){}

std::pair<int, int> PerspectiveProjection::project(int &x, int &y, int &z) const {
	double adjustedZ = -z;
	double scale = _distance / (_distance + adjustedZ);
	int newX = x * scale;
	int newY = y * scale;
	return {newX, newY};
}