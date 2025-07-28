#ifndef MILITARYPROJECTION_HPP
# define MILITARYPROJECTION_HPP

#include "IProjection.hpp"

class MilitaryProjection : public IProjection{
	public:
		~MilitaryProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif