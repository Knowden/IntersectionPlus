#include "Solution.h"
#include "StringUtil.h"

using namespace std;

Solution::Solution() {
	this->line_map.max_load_factor(0.6f);
}

void Solution::add_component(std::string ori_input) {
	if (StringUtil::trim(ori_input).at(0) == 'L') {
		Line line(ori_input);
		if (line_map.count(line.k) == 0) {
			line_map[line.k] = *new vector<Line>();
		}
		line_map.at(line.k).push_back(line);
	}
	else {
		Circle circle(ori_input);
		circle_list.push_back(circle);
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
	for (unordered_map<long double, vector<Line>>::iterator i = line_map.begin(); i != line_map.end(); i++) {
		unordered_map<long double, vector<Line>>::iterator temp = i;
		temp++;
		for (unordered_map<long double, vector<Line>>::iterator j = temp; j != line_map.end(); j++) {
			vector<Line> line_list1 = i->second;
			vector<Line> line_list2 = j->second;

			for (Line line1 : line_list1) {
				for (Line line2 : line_list2) {
					Point* p = line1.get_intersection_with(line2);
					if (p != nullptr) {
						result_set.insert(*p);
					}
				}
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
	for (unordered_map<long double, vector<Line>>::iterator i = line_map.begin(); i != line_map.end(); i++) {
		vector<Line> line_list = i->second;
		for (Line line : line_list) {
			for (Circle circle : circle_list) {
				vector<Point> v = circle.getIntersectionWith(line);
				for (Point point : v) {
					result_set.insert(point);
				}
			}
		}
	}
}