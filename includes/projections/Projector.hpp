/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:39:42 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 15:35:07 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTOR_HPP
# define PROJECTOR_HPP

# include <stdexcept>
# include "../../includes/projections/IProjection.hpp"
# include "../../includes/projections/IsometricProjection.hpp"
# include "../../includes/projections/OrthographicProjection.hpp"
# include "../../includes/projections/PerspectiveProjection.hpp"
# include "../../includes/projections/TrimetricProjection.hpp"
# include "../../includes/projections/DimetricProjection.hpp"
# include "../../includes/projections/CabinetProjection.hpp"
# include "../../includes/projections/CavalierProjection.hpp"
# include "../../includes/projections/MilitaryProjection.hpp"
# include "../../includes/projections/RecursiveDepthProjection.hpp"
# include "../../includes/projections/HyperbolicProjection.hpp"

class Projector{
	private:
		IProjection *_selectedProjection;
		
		IsometricProjection *_isometric;
		PerspectiveProjection *_perspective;
		OrthographicProjection *_orthographic;
		TrimetricProjection *_trimetric;
		CabinetProjection *_cabinet;
		DimetricProjection *_dimetric;
		CavalierProjection *_cavalier;
		MilitaryProjection *_military;
		RecursiveDepth *_recursive;
		HyperbolicProjection *_hyperbolic;

	public:
		class BadProjectionException : public std::exception{
			const char *what() const throw();	
		};
		
		Projector();
		~Projector();

		IProjection *getProjection();

		void setType(int type);
};

#endif