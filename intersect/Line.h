#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

class Point;
class Circle;

/**
通常而言，k和b的定义与常规数学定义一致
特别的，当k不存在的时候（无穷大），k采用Integer的最大值表示，此时的b表示竖线与x轴的交点
*/
class Line {
public:
	long double k; // 斜率
	long double b; // 截距

	Line(const std::string& ori_input);
	Line(long double k, long double b);

	Point* get_intersection_with(Line& another);
	std::vector<Point> get_intersection_with(Circle& another);
};

#endif // !LINE_H