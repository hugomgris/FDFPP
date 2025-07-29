/**
 * @file Projector.cpp
 * @brief Implements the Projector class, which manages different 3D to 2D projection methods.
 *
 * The Projector class serves as a factory and manager for various projection algorithms,
 * allowing dynamic switching between different projection types such as isometric,
 * perspective, orthographic, and other specialized projections for 3D wireframe rendering.
 */

#include "../../includes/projections/Projector.hpp"

/**
 * @brief Constructs a Projector object and initializes all available projection types.
 * 
 * Creates instances of all supported projection algorithms and sets up the projection
 * management system. Each projection type is instantiated and ready for use.
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
 * @brief Destructor for the Projector class.
 * 
 * Properly deallocates memory for all projection instances to prevent memory leaks.
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
 * @brief Sets the active projection type based on the provided type identifier.
 * 
 * Switches between different projection algorithms using a numeric identifier.
 * Each number corresponds to a specific projection type:
 * 1: Isometric, 2: Perspective, 3: Orthographic, 4: Trimetric, 5: Dimetric,
 * 6: Cabinet, 7: Cavalier, 8: Military, 9: Recursive Depth, 10: Hyperbolic,
 * 11: Conic, 12: Spherical Conic
 * 
 * @param type Integer identifier for the desired projection type (1-12).
 * @throws BadProjectionException If the type parameter is outside the valid range.
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

/**
 * @brief Returns the error message for invalid projection selection.
 * 
 * @return C-style string describing the error and valid range of projection types.
 */
const char *Projector::BadProjectionException::what() const throw(){
	return ("Bad projection selection! (Try with values 1-11 or use 'help' as argument for further instructions)");
}