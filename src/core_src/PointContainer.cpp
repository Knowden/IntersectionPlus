#include "PointContainer.h"

void PointContainer::add_point(Point p) {
	if (data.count(p.x) == 0) {
		data[p.x] = *new std::unordered_set<long double>();
	}

	data[p.x].insert(p.y);
}

int PointContainer::get_amount_of_points() {
	int total_amount = 0;
	for (std::unordered_map<long double, std::unordered_set<long double>>::iterator i = data.begin(); i != data.end(); i++) {
		total_amount += i->second.size();
	}

	return total_amount;
}
