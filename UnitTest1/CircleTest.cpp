#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <set>
#include "../intersect/Circle.h"
#include "../intersect/Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircleTest {
	TEST_CLASS(CircleTest) {
public:

	TEST_METHOD(TestApartWithAnother) {
		Circle c1("C 0 0 1");
		Circle c2("C 5 0 1");

		std::vector<Point> result = c1.getIntersectionWith(c2);
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(0, (int)set.size());
	}

	TEST_METHOD(TestTangentWithAnother) {
		Circle c1("C 0 0 1");
		Circle c2("C 2 0 1");

		std::vector<Point> result = c1.getIntersectionWith(c2);
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(1, (int)set.size());
	}

	TEST_METHOD(TestIntersIntersectWithAnother) {
		Circle c1("C 0 0 3");
		Circle c2("C 4 0 2");

		std::vector<Point> result = c1.getIntersectionWith(c2);
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(2, (int)set.size());
	}

	TEST_METHOD(TestIncisionWithAnother) {
		Circle c1("C 0 0 3");
		Circle c2("C 2 0 1");

		std::vector<Point> result = c1.getIntersectionWith(c2);
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(1, (int)set.size());
	}

	TEST_METHOD(TestContainedWithAnother) {
		Circle c1("C 0 0 3");
		Circle c2("C 1 0 1");

		std::vector<Point> result = c1.getIntersectionWith(c2);
		std::set<Point> set(result.begin(), result.end());
		Assert::AreEqual(0, (int)set.size());
	}
	};
}
