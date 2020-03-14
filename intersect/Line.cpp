#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include "StringUtil.h"
#include <algorithm>

using namespace std;

Line::Line(const string& ori_input) {
    vector<string> infos = StringUtil::split(StringUtil::trim(ori_input), " ");
    const Point p1(stod(infos.at(1)), stod(infos.at(2)));
    const Point p2(stod(infos.at(3)), stod(infos.at(4)));

    long double k = 0;
    long double b = 0;
    if (p1.x == p2.x) {
        k = INT_MAX;
        b = p1.x;
    }
    else {
        k = (p1.y - p2.y) / (p1.x - p2.x);
        b = p1.y - k * p1.x;
    }

    this->k = k;
    this->b = b;

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

Line::Line(long double k, long double b) {
    this->k = k;
    this->b = b;
    this->leftLimit = (long double) INT_MIN;
    this->rightLimit = INT_MAX;

    this->type = LineType::STRAIGHT;
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

    if (this->k == another.k) {
        return result;
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

    return result;
}

vector<Point> Line::get_intersection_with(Circle& another) {
    return another.getIntersectionWith(*this);
}