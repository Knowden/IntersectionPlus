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

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(0, (int)result.size());
	}

	TEST_METHOD(TestLineWithNotParallelWithAnother) {
		Line line1("L 1 1 2 2");
		Line line2("L -1 1 1 -1");

		std::vector<Point> result = line1.get_intersection_with(line2);

		Assert::AreEqual(1, (int) result.size());

		Point point = result.at(0);

		Assert::AreEqual(0.0, (double)point.x);
		Assert::AreEqual(0.0, (double)point.y);
	}

	TEST_METHOD(TestLinePartFromCricle) {
		Line line("L 0 10 10 0");
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
		Line line("L 0 1 1 0");
		Circle circle("C 0 0 1");

		std::vector<Point> result = line.get_intersection_with(circle);

		Assert::AreEqual(2, (int)result.size());
	}

	TEST_METHOD(TestBuildNormalLineSegment) {
		Line line("S 1 1 2 2");

		Assert::AreEqual(1, (int)line.leftLimit);
		Assert::AreEqual(2, (int)line.rightLimit);
	}

	TEST_METHOD(TestBuildLineSegmentWithKNotExist) {
		Line line("S 1 1 1 10");

		Assert::AreEqual(1, (int)line.leftLimit);
		Assert::AreEqual(10, (int)line.rightLimit);
	}

	TEST_METHOD(TestBuildNormalRayPointRight) {
		Line line("R 1 1 10 10");

		Assert::AreEqual(1, (int)line.leftLimit);
		Assert::AreEqual(INT_MAX, (int)line.rightLimit);
	}

	TEST_METHOD(TestBuildNormalRayPointLeft) {
		Line line("R 1 1 -10 -10");

		Assert::AreEqual(INT_MIN, (int)line.leftLimit);
		Assert::AreEqual(1, (int)line.rightLimit);
	}

	TEST_METHOD(TestBuildRayWithKNotExistPointUp) {
		Line line("R 1 1 1 10");

		Assert::AreEqual(1, (int)line.leftLimit);
		Assert::AreEqual(INT_MAX, (int)line.rightLimit);
	}

	TEST_METHOD(TestBuildRayWithKNotExistPointDown) {
		Line line("R 1 1 1 -10");

		Assert::AreEqual(INT_MIN, (int)line.leftLimit);
		Assert::AreEqual(1, (int)line.rightLimit);
	}

	};
}
