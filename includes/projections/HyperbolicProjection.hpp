/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LayeredProjection.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:20:02 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:21:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HYPERBOLICPROJECTION_HPP
# define HYPERBOLICPROJECTION_HPP

# include "IProjection.hpp"

class HyperbolicProjection : public IProjection{
		private:
			double _distance;
		
		public:
			HyperbolicProjection(double distance = 1000.0);
			~HyperbolicProjection();

			std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif