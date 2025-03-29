/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FishEyeProjection.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:47:04 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:58:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECURSIVEDEPTH_HPP
# define RECURSIVEDEPTH_HPP

# include <algorithm>

# include "IProjection.hpp"

class RecursiveDepth : public IProjection{
	public:
		~RecursiveDepth();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif