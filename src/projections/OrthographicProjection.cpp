#include "../../includes/projections//OrthographicProjection.hpp"

OrthographicProjection::~OrthographicProjection(){}

std::pair<int, int> OrthographicProjection::project(int &x, int &y, int &z) const{
		(void)z;
		return {x, y};
}
