#/**
# * @file Projector.hpp
# * @class Projector
# * @brief Manages and selects projection types for rendering 3D maps.
# *
# * The Projector class holds instances of all supported projection types and allows switching between them.
# * Provides access to the currently selected projection and handles errors for invalid selections.
# */

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
# include "../../includes/projections/ConicProjection.hpp"
# include "../../includes/projections/SphericalConicProjection.hpp"

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
		ConicProjection *_conic;
		SphericalConicProjection *_spherical;

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