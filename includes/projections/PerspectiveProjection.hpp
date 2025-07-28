#ifndef PERSPECTIVEPROJECTION_HPP
# define PERSPECTIVEPROJECTION_HPP

# include "IProjection.hpp"

class PerspectiveProjection : public IProjection{
		private:
			double _distance;
		
		public:
			PerspectiveProjection(double distance = 1000.0);
			~PerspectiveProjection();

			std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif