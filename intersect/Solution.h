#ifndef SOLUTION_H
#define SOLUTION_H

#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

#include "Line.h"
#include "Circle.h"
#include "Point.h"

class Solution {
private:
	std::unordered_map<long double, std::vector<Line>> line_map;
	std::vector<Circle> circle_list;
	std::unordered_set<Point> result_set;

	void count_line_with_line();
	void count_circle_with_circle();
	void count_line_with_circle();

public:
	Solution();

	void add_component(std::string ori_input);
	int count_result();
};

#endif
