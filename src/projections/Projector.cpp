/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:44:03 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 15:35:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/Projector.hpp"

Projector::Projector(){
	_isometric = new IsometricProjection();
	_perspective = new PerspectiveProjection();
	_orthographic = new OrthographicProjection();
	_trimetric = new TrimetricProjection();
	_dimetric = new DimetricProjection();
	_cabinet = new CabinetProjection();
	_cavalier = new CavalierProjection();
	_military = new MilitaryProjection();
	_fisheye = new RecursiveDepth();
	_hyperbolic = new HyperbolicProjection();
}

Projector::~Projector(){
	delete _isometric;
    delete _perspective;
    delete _orthographic;
    delete _trimetric;
    delete _dimetric;
    delete _cabinet;
    delete _cavalier;
    delete _military;
    delete _fisheye;
	delete _hyperbolic;
}

IProjection *Projector::getProjection(){
	return (_selectedProjection);
}

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
			_selectedProjection = _fisheye;
			break;
		case 10:
			_selectedProjection = _hyperbolic;
			break;
		default:
			throw(BadProjectionException());
	}
}

const char *Projector::BadProjectionException::what() const throw(){
	return ("Bad projection selection! (Try with values 1-9 or use 'help' as argument for further instructions)");
}