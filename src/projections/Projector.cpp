/**
# * @file Projector.cpp
# * @brief Implements the Projector class for managing and selecting projection types.
# *
# * The Projector class holds instances of all supported projection types and allows switching between them.
# * Provides access to the currently selected projection and handles errors for invalid selections.
# */


#include "../../includes/projections/Projector.hpp"

/**
 * @brief Constructs a Projector object and initializes all supported projection types.
 */
Projector::Projector(){
	_isometric = new IsometricProjection();
	_perspective = new PerspectiveProjection();
	_orthographic = new OrthographicProjection();
	_trimetric = new TrimetricProjection();
	_dimetric = new DimetricProjection();
	_cabinet = new CabinetProjection();
	_cavalier = new CavalierProjection();
	_military = new MilitaryProjection();
	_recursive = new RecursiveDepth();
	_hyperbolic = new HyperbolicProjection();
	_conic = new ConicProjection();
	_spherical = new SphericalConicProjection();
}

/**
 * @brief Destructor for Projector. Cleans up all projection type instances.
 */
Projector::~Projector(){
	delete _isometric;
	delete _perspective;
	delete _orthographic;
	delete _trimetric;
	delete _dimetric;
	delete _cabinet;
	delete _cavalier;
	delete _military;
	delete _recursive;
	delete _hyperbolic;
	delete _conic;
	delete _spherical;
}

IProjection *Projector::getProjection(){
	return (_selectedProjection);

}

/**
 * @brief Sets the active projection type by integer code.
 *
 * Switches the selected projection to the corresponding type. Throws BadProjectionException for invalid codes.
 * @param type Integer code for the projection type (1-12).
 */
void Projector::setType(int type){
	switch (type){
		case 1:
			_selectedProjection = _isometric;
			break;
		case 2:
			_selectedProjection = _perspective;
			break;
		case 3:
			_selectedProjection = _orthographic;
			break;
		case 4:
			_selectedProjection = _trimetric;
			break;
		case 5:
			_selectedProjection = _dimetric;
			break;
		case 6:
			_selectedProjection = _cabinet;
			break;
		case 7:
			_selectedProjection = _cavalier;
			break;
		case 8:
			_selectedProjection = _military;
			break;
		case 9:
			_selectedProjection = _recursive;
			break;
		case 10:
			_selectedProjection = _hyperbolic;
			break;
		case 11:
			_selectedProjection = _conic;
			break;
		case 12:
			_selectedProjection = _spherical;
			break;
		default:
			throw(BadProjectionException());
	}
}

const char *Projector::BadProjectionException::what() const throw(){
	return ("Bad projection selection! (Try with values 1-11 or use 'help' as argument for further instructions)");
}