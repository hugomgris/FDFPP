#ifndef IPROJECTION_HPP
# define IPROJECTION_HPP

# include <utility>
# include <cmath>

class IProjection {
	public:
		virtual ~IProjection(){}
		virtual std::pair<int, int> project(int &x, int &y, int &z) const = 0;
};

#endif