#ifndef CAVALIERPROJECTION_HPP
# define CAVALIERPROJECTION_HPP

#include "IProjection.hpp"

class CavalierProjection : public IProjection{
	public:
		~CavalierProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif