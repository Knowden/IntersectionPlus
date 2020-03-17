#include "core.h"

using namespace std;

void core::add_component(string component) {
	s.add_component(component);
}

unordered_set<Point> core::get_all_intersection(bool force) {
	if (s.result_set.size() == 0 || force) {
		s.count_result();
	}

	return s.result_set;
}

vector<Line> core::get_all_line() {
	return s.line_list;
}

vector<Circle> core::get_all_circle() {
	return s.circle_list;
}
