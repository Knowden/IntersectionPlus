#ifndef POINT_CONTAINER_H
#define POINT_CONTAINER_H

#include "Point.h"
#include <unordered_map>
#include <unordered_set>

class PointContainer {
private:
	std::unordered_map<long double, std::unordered_set<long double>> data;

public:
	void add_point(Point p);
	int get_amount_of_points();
};


#endif // !POINT_CONTAINER_H



