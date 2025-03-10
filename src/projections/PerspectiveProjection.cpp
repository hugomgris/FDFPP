/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerspectiveProjection.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:22:34 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/PerspectiveProjection.hpp"

PerspectiveProjection::PerspectiveProjection(double distance) : _distance(distance) {}

PerspectiveProjection::~PerspectiveProjection(){}

std::pair<int, int> PerspectiveProjection::project(int &x, int &y, int &z) const {
				double scale = _distance / (_distance + z);
				int newX = x * scale;
				int newY = y * scale;
				return {newX, newY};
}