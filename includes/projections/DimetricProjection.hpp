/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DimetricProjection.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:47:04 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:58:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIMETRICPROJECTION_HPP
# define DIMETRICPROJECTION_HPP

#include "IProjection.hpp"

class DimetricProjection : public IProjection{
	public:
		~DimetricProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif