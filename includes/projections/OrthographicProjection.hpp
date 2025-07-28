#ifndef ORTOGRAPHICPROJECTION_HPP
# define ORTOGRAPHICPROJECTION_HPP

# include "IProjection.hpp"

class OrthographicProjection : public IProjection{
	public:
		~OrthographicProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif