#include "core.h"

using namespace std;

void core::add_component(string component) {
	s.add_component(component);
}

void core::delete_line_component(int id) {
	s.delete_line_component(id);
}

void core::delete_circle_component(int id) {
	s.delete_circle_component(id);
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
