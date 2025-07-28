#ifndef HYPERBOLICPROJECTION_HPP
# define HYPERBOLICPROJECTION_HPP

# include "IProjection.hpp"

class HyperbolicProjection : public IProjection{
		public:
			HyperbolicProjection();
			~HyperbolicProjection();

			std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif