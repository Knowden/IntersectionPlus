#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>
#include <iostream>

class Point;
class Circle;

enum class LineType {
	SEGMENT, RAY, STRAIGHT
};

/**
线通用类，同时支持直线、射线、线段

通常而言，k和b的定义与常规数学定义一致
特别的，当k不存在的时候（无穷大），k采用Integer的最大值表示，此时的b表示竖线与x轴的交点

通常而言，leftLimit和rightLimit代表x坐标的左右边界，用于处理线段和射线的问题
当边界正无穷大时，用INT_MAX表示，当为负无穷时为INT_MIN
特别的，对于斜率不存在的情况，leftLimit代表y的下界，rightLimit代表y的上界
*/
class Line {
private:
	static int AUTO_INCREMENT_ID;

	std::vector<std::string> split_input_to_infos(std::string ori_input);

	void build_straight_line(std::vector<std::string> cleaned_input);
	void build_ray(std::vector<std::string> cleaned_input);
	void build_segment_line(std::vector<std::string> cleaned_input);

	std::vector<Point> handle_line_collinear(Line another);

	void remove_impossible_points(std::vector<Point>& result, Line line);

public:
	long double k; // 斜率
	long double b; // 截距

	long double leftLimit;
	long double rightLimit;

	LineType type;

	int id;

	Line(const std::string& ori_input);
	Line(long double k, long double b);

	std::vector<Point> get_intersection_with(Line& another);
	std::vector<Point> get_intersection_with(Circle& another);

	bool contains_point(Point point);

	friend std::ostream& operator<<(std::ostream& out, const Line& line);
};

#endif // !LINE_H