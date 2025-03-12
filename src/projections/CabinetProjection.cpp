/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CabinetProjection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 14:25:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/CabinetProjection.hpp"

CabinetProjection::~CabinetProjection(){}

std::pair<int, int> CabinetProjection::project(int &x, int &y, int &z) const {
    double factor = 0.5;
    int newX = x + z * factor * cos(M_PI / 4);
    int newY = y - z * factor * sin(M_PI / 4);
    return {newX, newY};
}