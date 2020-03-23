#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include "StringUtil.h"
#include "MathUtil.h"
#include <algorithm>
#include <iostream>
#include <regex>

using namespace std;

int Line::AUTO_INCREMENT_ID = 1;

ostream& operator<<(ostream& out, Line& line) {
    out << "y = " << line.k << "x + " << line.b;
    return out;
}


Line::Line(const string& ori_input) {
    vector<string> infos = split_input_to_infos(ori_input);
    
    for (int i = 1; i <= 4; i++) {
        double value = stod(infos.at(i));
        if (value > 100000 || value < -100000) {
            string message = "存在坐标超出范围限制: " + ori_input;
            throw exception(message.c_str());
        }
    }

    const Point p1(stod(infos.at(1)), stod(infos.at(2)));
    const Point p2(stod(infos.at(3)), stod(infos.at(4)));
    if (p1 == p2) {
        string message = "存在输入点重合: " + ori_input;
        throw exception(message.c_str());
    }

    long double k = 0;
    long double b = 0;
    if (MathUtil::d_equal(p1.x, p2.x)) {
        k = INT_MAX;
        b = p1.x;
    }
    else {
        k = (p1.y - p2.y) / (p1.x - p2.x);
        b = p1.y - k * p1.x;
    }

    this->k = k;
    this->b = b;
    this->id = AUTO_INCREMENT_ID++;

    if (infos.at(0) == "L") {
        build_straight_line(infos);
    }
    else if (infos.at(0) == "R") {
        build_ray(infos);
    }
    else {
        build_segment_line(infos);
    }
}

vector<string> Line::split_input_to_infos(string ori_input) {
    vector<string> result;

    std::regex split_flag("\\s+");
    std::sregex_token_iterator pos(ori_input.begin(), ori_input.end(), split_flag, -1);
    decltype(pos) end;
    for (; pos != end; ++pos) {
        result.push_back(pos->str());
    }

    return result;
}

Line::Line(long double k, long double b) {
    this->k = k;
    this->b = b;
    this->leftLimit = (long double) INT_MIN;
    this->rightLimit = INT_MAX;

    this->type = LineType::STRAIGHT;
    this->id = Line::AUTO_INCREMENT_ID++;
}

void Line::build_straight_line(vector<string> infos) {
    this->leftLimit = (long double)INT_MIN;
    this->rightLimit = INT_MAX;

    this->type = LineType::STRAIGHT;
}

void Line::build_segment_line(vector<string> infos) {
    if (this->k != INT_MAX) {
        int x1 = stoi(infos.at(1));
        int x2 = stoi(infos.at(3));
        
        this->leftLimit = min(x1, x2);
        this->rightLimit = max(x1, x2);
    }
    else {
        int y1 = stoi(infos.at(2));
        int y2 = stoi(infos.at(4));

        this->leftLimit = min(y1, y2);
        this->rightLimit = max(y1, y2);
    }

    this->type = LineType::SEGMENT;
}

void Line::build_ray(vector<string> infos) {
    if (this->k != INT_MAX) {
        int x1 = stoi(infos.at(1));
        int x2 = stoi(infos.at(3));

        if (x1 < x2) {
            this->leftLimit = x1;
            this->rightLimit = INT_MAX;
        }
        else {
            this->leftLimit = (long double)INT_MIN;
            this->rightLimit = x1;
        }
    }
    else {
        int y1 = stoi(infos.at(2));
        int y2 = stoi(infos.at(4));

        if (y1 > y2) {
            this->leftLimit = (long double)INT_MIN;
            this->rightLimit = y1;
        }
        else {
            this->leftLimit = y1;
            this->rightLimit = INT_MAX;
        }
    }

    this->type = LineType::RAY;
}

vector<Point> Line::get_intersection_with(Line& another) {
    vector<Point> result;

    if (MathUtil::d_equal(this->k, another.k)) {
        if (this->b != another.b) {
            return result;
        }
        else {
            return handle_line_collinear(another);
        }
    }

    if (this->k == INT_MAX) {
        result.push_back(Point(this->b, another.k * this->b + another.b));
    }
    else if (another.k == INT_MAX) {
        result.push_back(Point(another.b, this->k * another.b + this->b));
    }
    else {
        long double x = (another.b - this->b) / (this->k - another.k);
        long double y = this->k * x + this->b;

        result.push_back(Point(x, y));
    }

    remove_impossible_points(result, another);
    return result;
}

/*
这个函数十分重要且情况十分复杂，所以特别记录一下各种分支
1. 共线没有交点
2. 共线一个交点
3. 共线多个交点（重合，无数个交点）

下面留一些分析思路，便于日后查错
1. 若两线中有直线，则必为无数个交点，抛异常
2. 当两线都不为直线时，可能为0或1或无穷个，根据左右limit判断
*/
vector<Point> Line::handle_line_collinear(Line another) {
    if (this->type == LineType::STRAIGHT || another.type == LineType::STRAIGHT) {
        string line_str = "x = " + to_string(this->b);
        string message = "存在无穷交点的线: " + line_str;
        throw exception(message.c_str());
    }

    vector<Point> result;

    if (this->rightLimit < another.leftLimit || another.rightLimit < this->leftLimit) {
        // 没有公共交点
        return result;
    }
    else if (MathUtil::d_equal(this->rightLimit, another.leftLimit)) {
        // 有一个公共交点
        if (this->k == INT_MAX) {
            result.push_back(Point(this->b, this->rightLimit));
        }
        else {
            const long double y = this->k * this->rightLimit + this->b;
            result.push_back(Point(this->rightLimit, y));
        }
    }
    else if (MathUtil::d_equal(another.rightLimit, this->leftLimit)) {
        if (another.k == INT_MAX) {
            result.push_back(Point(another.b, another.rightLimit));
        }
        else {
            const long double y = another.k * another.rightLimit + another.b;
            result.push_back(Point(another.rightLimit, y));
        }
    }
    else {
        // 无穷个交点
        string line_str = "y = " + to_string(this->k) + "*x + (" + to_string(this->b) + ")";
        string message = "存在无穷交点的线: " + line_str;
        throw exception(message.c_str());
    }

    return result;
}

vector<Point> Line::get_intersection_with(Circle& another) {
    return another.getIntersectionWith(*this);
}

void Line::remove_impossible_points(vector<Point>& result, Line line) {
    vector<Point>::iterator iter_point = result.begin();

    while (iter_point != result.end()) {
        if (!this->contains_point(*iter_point) || !line.contains_point(*iter_point)) {
            iter_point = result.erase(iter_point);
        }
        else {
            iter_point++;
        }
    }
}

bool Line::contains_point(Point point) {
    if (this->k == INT_MAX) {
        return point.y >= this->leftLimit && point.y <= this->rightLimit;
    }
    else {
        return point.x >= this->leftLimit && point.x <= this->rightLimit;
    }
}