#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Point.h"
#include "Line.h"
#include "Solution.h"
#include "Circle.h"

class _declspec(dllexport) core {
private:
	Solution s;

public:
	void add_component(std::string component);
	std::unordered_set<Point> get_all_intersection(bool force);
	std::vector<Line> get_all_line();
	std::vector<Circle> get_all_circle();
};