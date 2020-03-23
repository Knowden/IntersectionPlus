#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <vector>
#include <iostream>

class Point;
class Line;

class Circle {
private:
	static int AUTO_INCREMENT_ID;

	std::vector<std::string> splitOriInputIntoInfos(std::string ori_input);

	std::vector<Point> calculatePointsAtX(long double x);
	std::vector<Point> calculateIntersectionWithNormalLine(Line& line);

	void removeImpossiblePoints(std::vector<Point>& result, Line line);

public:
	Point* center;
	long double r;

	int id;

	Circle(const std::string& input);
	Circle(long double x, long double y, long double r);
	
	friend std::ostream& operator<<(std::ostream& out, const Circle& circle);

	std::vector<Point> getIntersectionWith(Line& line);
	std::vector<Point> getIntersectionWith(Circle& another);
};

#endif // !CIRCLE_H