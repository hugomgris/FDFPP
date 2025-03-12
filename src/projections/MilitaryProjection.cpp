/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MilitaryProjection.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 14:24:53 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/MilitaryProjection.hpp"

MilitaryProjection::~MilitaryProjection(){}

std::pair<int, int> MilitaryProjection::project(int &x, int &y, int &z) const {
    int newX = x;
    int newY = y - z;
    return {newX, newY};
}