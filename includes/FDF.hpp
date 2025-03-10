/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:06:36 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 15:35:42 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HPP
# define FDF_HPP

# include <iostream>
# include <vector>
# include "MLXHandler.hpp"
# include "projections/OrthographicProjection.hpp"
# include "projections/IsometricProjection.hpp"
# include "projections/PerspectiveProjection.hpp"

class FDF{
	private:
		std::vector<std::string> &_map;
		IProjection *_projection;
		MLXHandler _MLXHandler;
	
	public:
		FDF(std::vector<std::string> map, IProjection *projection, MLXHandler &MLXHandler);
		~FDF();
};

#endif