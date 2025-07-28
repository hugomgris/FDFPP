#ifndef CABINETPROJECTION_HPP
# define CABINETPROJECTION_HPP

#include "IProjection.hpp"

class CabinetProjection : public IProjection{
	public:
		~CabinetProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif