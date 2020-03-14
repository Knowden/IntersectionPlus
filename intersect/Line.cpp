#include "Circle.h"
#include "Point.h"
#include "Line.h"
#include "StringUtil.h"

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

    this->Line::Line(k, b);
}

Line::Line(long double k, long double b) {
    this->k = k;
    this->b = b;
}

Point* Line::get_intersection_with(Line& another) {
    if (this->k == another.k) {
        return nullptr;
    }

    if (this->k == INT_MAX) {
        return new Point(this->b, another.k * this->b + another.b);
    }
    else if (another.k == INT_MAX) {
        return new Point(another.b, this->k * another.b + this->b);
    }
    else {
        long double x = (another.b - this->b) / (this->k - another.k);
        long double y = this->k * x + this->b;

        return new Point(x, y);
    }
}

vector<Point> Line::get_intersection_with(Circle& another) {
    return another.getIntersectionWith(*this);
}
