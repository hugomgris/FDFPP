#ifndef ISOMETRICPROJECTION_HPP
# define ISOMETRICPROJECTION_HPP

#include "IProjection.hpp"

class IsometricProjection : public IProjection{
	public:
		~IsometricProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif