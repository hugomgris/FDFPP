/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OrthographicProjection.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:46:01 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:18:51 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections//OrthographicProjection.hpp"

OrthographicProjection::~OrthographicProjection(){}

std::pair<int, int> OrthographicProjection::project(int &x, int &y, int &z) const{
		(void)z;
		return {x, y};
}
