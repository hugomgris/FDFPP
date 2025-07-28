#ifndef DIMETRICPROJECTION_HPP
# define DIMETRICPROJECTION_HPP

#include "IProjection.hpp"

class DimetricProjection : public IProjection{
	public:
		~DimetricProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif