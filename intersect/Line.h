#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>

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
	void build_straight_line(std::vector<std::string> cleaned_input);
	void build_ray(std::vector<std::string> cleaned_input);
	void build_segment_line(std::vector<std::string> cleaned_input);

	void remove_impossible_points(std::vector<Point>& result, Line line);
	bool is_appear_in_line(Point point, Line line);

public:
	long double k; // б��
	long double b; // �ؾ�

	long double leftLimit;
	long double rightLimit;

	LineType type;

	Line(const std::string& ori_input);
	Line(long double k, long double b);

	std::vector<Point> get_intersection_with(Line& another);
	std::vector<Point> get_intersection_with(Circle& another);
};

#endif // !LINE_H