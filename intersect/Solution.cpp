#include "Solution.h"
#include "StringUtil.h"

using namespace std;

void Solution::add_component(std::string ori_input) {
	if (StringUtil::trim(ori_input).at(0) == 'C') {
		circle_list.push_back(Circle(ori_input));
	}
	else {
		line_list.push_back(Line(ori_input));
	}
}

int Solution::count_result() {
	result_set = *new unordered_set<Point>(1000000);
	result_set.max_load_factor(0.6f);

	count_line_with_line();
	count_circle_with_circle();
	count_line_with_circle();
	
	return (int)result_set.size();
}

void Solution::count_line_with_line() {
	for (int i = 0; i < (int) line_list.size(); i++) {
		for (int j = i + 1; j < (int) line_list.size(); j++) {
			vector<Point> result = (line_list.at(i)).get_intersection_with(line_list.at(j));
			for (Point point : result) {
				result_set.insert(point);
			}
		}
	}
}

void Solution::count_circle_with_circle() {
	for (int i = 0; i < (int) circle_list.size(); i++) {
		for (int j = i + 1; j < (int)circle_list.size(); j++) {
			vector<Point> v = circle_list.at(i).getIntersectionWith(circle_list.at(j));
			for (Point point : v) {
				result_set.insert(point);
			}
		}
	}
}

void Solution::count_line_with_circle() {
	for (Line line : line_list) {
		for (Circle circle : circle_list) {
			vector<Point> result = line.get_intersection_with(circle);
			
			for (Point point : result) {
				result_set.insert(point);
			}
		}
	}
}