/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerspectiveProjection.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:20:02 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:21:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSPECTIVEPROJECTION_HPP
# define PERSPECTIVEPROJECTION_HPP

# include "IProjection.hpp"

class PerspectiveProjection : public IProjection{
		private:
			double _distance;
		
		public:
			PerspectiveProjection(double distance = 1000.0);
			~PerspectiveProjection();

			std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif