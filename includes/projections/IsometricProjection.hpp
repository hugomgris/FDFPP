/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsometricProjection.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:47:04 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:23:21 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISOMETRICPROJECTION_HPP
# define ISOMETRICPROJECTION_HPP

#include "IProjection.hpp"

class IsometricProjection : public IProjection{
	public:
		~IsometricProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif