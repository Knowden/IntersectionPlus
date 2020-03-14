#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <set>
#include "../intersect/Point.h"
#include "../intersect/Line.h"
#include "../intersect/Circle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineTest {
	TEST_CLASS(LineTest) {
public:

	TEST_METHOD(TestNormalInit) {
		std::string input = "L 1 1 2 2";

		Line line(input);

		Assert::AreEqual(1.0, (double)line.k);
		Assert::AreEqual(0.0, (double)line.b);
	}

	TEST_METHOD(TestInitWithKEqual0) {
		std::string input = "L 1 1 2 1";

		Line line(input);

		Assert::AreEqual(0.0, (double)line.k);
		Assert::AreEqual(1.0, (double)line.b);
	}

	TEST_METHOD(TestInitWithKEqualInf) {
		std::string input = "L 1 3 1 5";

		Line line(input);

		Assert::AreEqual((double)INT_MAX, (double)line.k);
		Assert::AreEqual(1.0, (double)line.b);
	}

	TEST_METHOD(TestLineParallelWithAnother) {
		Line line1("L 1 1 2 2");
		Line line2("L 1 0 2 1");

		Point* result = line1.get_intersection_with(line2);

		Assert::IsNull(result);
	}

	TEST_METHOD(TestLineWithNotParallelWithAnother) {
		Line line1("L 1 1 2 2");
		Line line2("L -1 1 1 -1");

		Point* result = line1.get_intersection_with(line2);

		Assert::AreEqual(0.0, (double)result->x);
		Assert::AreEqual(0.0, (double)result->y);
	}

	TEST_METHOD(TestLinePartFromCricle) {
		Line line(-1, 10);
		Circle circle("C 0 0 1");

		std::vector<Point> result = line.get_intersection_with(circle);
		
		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestLineTangentWithCircle) {
		Line line(-1, sqrt(2));
		Circle circle("C 0 0 1");

		std::vector<Point> result = line.get_intersection_with(circle);
		
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(1, (int)set.size());
	}

	TEST_METHOD(TestLineIntersectWithCircle) {
		Line line(-1, 1);
		Circle circle("C 0 0 1");

		std::vector<Point> result = line.get_intersection_with(circle);

		Assert::AreEqual(2, (int)result.size());
	}

	};
}
