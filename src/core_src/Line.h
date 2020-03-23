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
��ͨ���࣬ͬʱ֧��ֱ�ߡ����ߡ��߶�

ͨ�����ԣ�k��b�Ķ����볣����ѧ����һ��
�ر�ģ���k�����ڵ�ʱ������󣩣�k����Integer�����ֵ��ʾ����ʱ��b��ʾ������x��Ľ���

ͨ�����ԣ�leftLimit��rightLimit����x��������ұ߽磬���ڴ����߶κ����ߵ�����
���߽��������ʱ����INT_MAX��ʾ����Ϊ������ʱΪINT_MIN
�ر�ģ�����б�ʲ����ڵ������leftLimit����y���½磬rightLimit����y���Ͻ�
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
	long double k; // б��
	long double b; // �ؾ�

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