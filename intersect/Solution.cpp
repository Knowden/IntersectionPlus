#include "Solution.h"
#include "StringUtil.h"
#include <regex>

using namespace std;

void Solution::add_component(string ori_input) {
	string checked_input = normalize_string(ori_input);
	
	if (checked_input.at(0) == 'C') {
		circle_list.push_back(Circle(checked_input));
	}
	else {
		line_list.push_back(Line(checked_input));
	}
}

std::string Solution::normalize_string(string ori_input) {
	string trimed_str = StringUtil::trim(ori_input);
	string number = "((0)|([123456789]\\d{0,5}))";
	regex reg("^(([LRS]\\s+-?" + number + "\\s+-?" + number +"\\s+-?" + number + "\\s+-?" + number + ")|" +
			   "(C\\s+-?" + number + "\\s+-?" + number + "\\s+[123456789]\\d{0,5}))$");
	
	if (trimed_str.length() > 50 || !std::regex_match(trimed_str, reg)) {
		string msg = "输入格式存在错误 : " + ori_input;
		throw exception(msg.c_str());
	}

	return trimed_str;
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

void Solution::delete_line_component(int id) {
	for (auto i = line_list.begin(); i != line_list.end(); i++) {
		if ((*i).id == id) {
			line_list.erase(i);
			break;
		}
	}
}

void Solution::delete_circle_component(int id) {
	for (auto i = circle_list.begin(); i != circle_list.end(); i++) {
		if ((*i).id == id) {
			circle_list.erase(i);
			break;
		}
	}
}