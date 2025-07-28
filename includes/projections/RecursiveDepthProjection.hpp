#ifndef RECURSIVEDEPTHPROJECTION_HPP
# define RECURSIVEDEPTHPROJECTION_HPP

# include <algorithm>

# include "IProjection.hpp"

class RecursiveDepth : public IProjection{
	public:
		~RecursiveDepth();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif