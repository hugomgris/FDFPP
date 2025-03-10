/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IProjection.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:38:35 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:23:39 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPROJECTION_HPP
# define IPROJECTION_HPP

# include <utility>
# include <cmath>

class IProjection {
	public:
		virtual ~IProjection(){}
		virtual std::pair<int, int> project(int &x, int &y, int &z) const = 0;
};

#endif